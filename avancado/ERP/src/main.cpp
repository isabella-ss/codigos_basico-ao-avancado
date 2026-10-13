#include <QApplication>
#include <QMessageBox>

#include "database/Database.h"
#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("ERP Estoque e Vendas");

    QString error;

    if (!Database::connect(&error)) {
        QMessageBox::critical(
            nullptr,
            "Erro de conexão",
            "Não foi possível conectar ao MySQL:\n" + error
        );

        return 1;
    }

    MainWindow window;
    window.show();

    const int result = app.exec();

    Database::connection().close();

    return result;
}