#include "SalesService.h"
#include "../database/Database.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

bool SalesService::confirmSale(qint64 orderId, const QVector<SaleItem> &items, QString *error)
{
    auto db = Database::connection();
    auto fail = [&](const QString &message) {
        db.rollback();
        if (error)
            *error = message;
        return false;
    };

    if (orderId <= 0) {
        if (error) *error = "Identificador do pedido inválido.";
        return false;
    }
    if (items.isEmpty()) {
        if (error) *error = "O pedido não possui itens.";
        return false;
    }
    if (!db.transaction()) {
        if (error) *error = db.lastError().text();
        return false;
    }

    QSqlQuery order(db);
    order.prepare("SELECT status FROM pedidos WHERE id = ? FOR UPDATE");
    order.addBindValue(orderId);
    if (!order.exec())
        return fail(order.lastError().text());
    if (!order.next())
        return fail("Pedido não encontrado.");
    if (order.value(0).toString() != "ABERTO")
        return fail("O pedido não está aberto.");

    for (const auto &item : items) {
        if (item.productId <= 0 || item.quantity <= 0)
            return fail("Produto ou quantidade inválida.");

        QSqlQuery product(db);
        product.prepare(
            "SELECT preco_venda, estoque_atual FROM produtos "
            "WHERE id = ? AND ativo = TRUE FOR UPDATE"
        );
        product.addBindValue(item.productId);
        if (!product.exec())
            return fail(product.lastError().text());
        if (!product.next())
            return fail("Produto não encontrado ou inativo.");

        const QString unitPrice = product.value(0).toString();
        const int stock = product.value(1).toInt();
        if (stock < item.quantity)
            return fail("Estoque insuficiente para o produto ID " + QString::number(item.productId) + ".");

        QSqlQuery insertItem(db);
        insertItem.prepare(
            "INSERT INTO itens_pedido (pedido_id, produto_id, quantidade, preco_unitario) "
            "VALUES (?, ?, ?, ?)"
        );
        insertItem.addBindValue(orderId);
        insertItem.addBindValue(item.productId);
        insertItem.addBindValue(item.quantity);
        insertItem.addBindValue(unitPrice);
        if (!insertItem.exec())
            return fail(insertItem.lastError().text());

        QSqlQuery updateStock(db);
        updateStock.prepare(
            "UPDATE produtos SET estoque_atual = estoque_atual - ? "
            "WHERE id = ? AND estoque_atual >= ?"
        );
        updateStock.addBindValue(item.quantity);
        updateStock.addBindValue(item.productId);
        updateStock.addBindValue(item.quantity);
        if (!updateStock.exec() || updateStock.numRowsAffected() != 1)
            return fail(updateStock.lastError().text().isEmpty()
                ? "Não foi possível atualizar o estoque." : updateStock.lastError().text());

        QSqlQuery movement(db);
        movement.prepare(
            "INSERT INTO movimentacoes_estoque "
            "(produto_id, tipo, quantidade, motivo, pedido_id) "
            "VALUES (?, 'SAIDA', ?, ?, ?)"
        );
        movement.addBindValue(item.productId);
        movement.addBindValue(item.quantity);
        movement.addBindValue(QString("Venda do pedido %1").arg(orderId));
        movement.addBindValue(orderId);
        if (!movement.exec())
            return fail(movement.lastError().text());
    }

    // O total é calculado pelo MySQL usando os preços decimais armazenados em itens_pedido.
    QSqlQuery updateOrder(db);
    updateOrder.prepare(
        "UPDATE pedidos SET status = 'CONFIRMADO', "
        "valor_total = (SELECT COALESCE(SUM(quantidade * preco_unitario), 0) "
        "FROM itens_pedido WHERE pedido_id = ?) "
        "WHERE id = ? AND status = 'ABERTO'"
    );
    updateOrder.addBindValue(orderId);
    updateOrder.addBindValue(orderId);
    if (!updateOrder.exec() || updateOrder.numRowsAffected() != 1)
        return fail(updateOrder.lastError().text().isEmpty()
            ? "Não foi possível confirmar o pedido." : updateOrder.lastError().text());

    if (!db.commit()) {
        const QString message = db.lastError().text();
        db.rollback();
        if (error) *error = message;
        return false;
    }
    if (error) error->clear();
    return true;
}
