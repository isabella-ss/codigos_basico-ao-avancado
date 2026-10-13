#pragma once

#include <QString>
#include <QVector>
#include <QtGlobal>

struct SaleItem
{
    qint64 productId = 0;
    int quantity = 0;
};

class SalesService
{
public:
    // Usa o preço de venda registrado no banco; não aceita preço enviado pelo chamador.
    // O pedido precisa existir e estar com status ABERTO.
    static bool confirmSale(
        qint64 orderId,
        const QVector<SaleItem> &items,
        QString *error = nullptr
    );
};
