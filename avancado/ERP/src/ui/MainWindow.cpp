#include "MainWindow.h"

#include <QTabWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QWidget>
#include <QAbstractItemView>

#include "../database/Database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ERP - Estoque e Vendas");
    resize(1100, 700);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    tabs_ = new QTabWidget(central);
    layout->addWidget(tabs_);
    setCentralWidget(central);

    auto *toolbar = addToolBar("Operações");
    toolbar->setMovable(false);

    auto *addAction = toolbar->addAction("Novo registro");
    auto *saveAction = toolbar->addAction("Salvar alterações");
    auto *deleteAction = toolbar->addAction("Excluir registro");
    auto *refreshAction = toolbar->addAction("Atualizar");

    connect(addAction, &QAction::triggered, this, [this]() {
        auto *view = qobject_cast<QTableView *>(tabs_->currentWidget());
        auto *model = view ? qobject_cast<QSqlTableModel *>(view->model()) : nullptr;
        if (!model)
            return;

        const int row = model->rowCount();
        if (!model->insertRow(row)) {
            QMessageBox::warning(this, "ERP", model->lastError().text());
            return;
        }

        const int nameColumn = model->record().indexOf("nome");
        const int editColumn = nameColumn >= 0 ? nameColumn : 0;
        view->setCurrentIndex(model->index(row, editColumn));
        view->edit(model->index(row, editColumn));
    });

    connect(saveAction, &QAction::triggered, this, [this]() {
        auto *view = qobject_cast<QTableView *>(tabs_->currentWidget());
        auto *model = view ? qobject_cast<QSqlTableModel *>(view->model()) : nullptr;
        if (!model)
            return;

        // Encerra a edição ativa antes de enviar as alterações ao banco.
        view->setFocus();

        if (!model->submitAll()) {
            QMessageBox::warning(
                this, "Falha ao salvar",
                "Não foi possível salvar as alterações:\n" + model->lastError().text()
            );
            return;
        }

        model->select();
        QMessageBox::information(this, "ERP", "Alterações salvas com sucesso.");
    });

    connect(deleteAction, &QAction::triggered, this, [this]() {
        auto *view = qobject_cast<QTableView *>(tabs_->currentWidget());
        auto *model = view ? qobject_cast<QSqlTableModel *>(view->model()) : nullptr;
        if (!view || !model || !view->selectionModel())
            return;

        const int row = view->currentIndex().row();
        if (row < 0)
            return;

        if (QMessageBox::question(
                this, "Confirmar exclusão",
                "Deseja excluir o registro selecionado?"
            ) != QMessageBox::Yes) {
            return;
        }

        if (!model->removeRow(row) || !model->submitAll()) {
            const QString reason = model->lastError().text();
            model->revertAll();
            QMessageBox::warning(
                this, "Não foi possível excluir",
                "O registro pode estar relacionado a outros dados.\n" + reason
            );
        } else {
            model->select();
        }
    });

    connect(refreshAction, &QAction::triggered, this, [this]() {
        auto *view = qobject_cast<QTableView *>(tabs_->currentWidget());
        auto *model = view ? qobject_cast<QSqlTableModel *>(view->model()) : nullptr;
        if (!model)
            return;

        if (model->isDirty()) {
            const auto answer = QMessageBox::question(
                this, "Descartar alterações?",
                "Existem alterações não salvas. Deseja descartá-las e atualizar?"
            );
            if (answer != QMessageBox::Yes)
                return;
            model->revertAll();
        }

        if (!model->select())
            QMessageBox::warning(this, "Erro ao atualizar", model->lastError().text());
    });

    addTableTab("Produtos", "produtos");
    addTableTab("Clientes", "clientes");
    addTableTab("Fornecedores", "fornecedores");
    addTableTab("Pedidos", "pedidos");
    addTableTab("Itens dos pedidos", "itens_pedido");
    addTableTab("Movimentações", "movimentacoes_estoque");
}

void MainWindow::addTableTab(const QString &title, const QString &tableName)
{
    auto *view = new QTableView(this);
    auto *model = new QSqlTableModel(view, Database::connection());
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    if (!model->select()) {
        QMessageBox::warning(
            this, "Erro ao carregar " + title,
            model->lastError().text()
        );
    }

    view->setModel(model);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setAlternatingRowColors(true);
    view->setSortingEnabled(true);
    view->horizontalHeader()->setStretchLastSection(true);
    tabs_->addTab(view, title);
}
