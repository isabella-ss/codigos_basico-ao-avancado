#include "Database.h"
#include <QSqlError>
#include <QVariant>

namespace {
QString envOrDefault(const char *name, const QString &fallback = QString())
{
    const QByteArray value = qgetenv(name);
    return value.isEmpty() ? fallback : QString::fromLocal8Bit(value);
}
}

bool Database::connect(QString *error)
{
    QSqlDatabase db = QSqlDatabase::contains("erp_connection")
        ? QSqlDatabase::database("erp_connection")
        : QSqlDatabase::addDatabase("QMYSQL", "erp_connection");

    db.setHostName(envOrDefault("ERP_DB_HOST", "127.0.0.1"));
    db.setPort(envOrDefault("ERP_DB_PORT", "3306").toInt());
    db.setDatabaseName(envOrDefault("ERP_DB_NAME", "erp_estoque"));
    db.setUserName(envOrDefault("ERP_DB_USER", "erp_app"));
    db.setPassword(envOrDefault("ERP_DB_PASSWORD"));

    if (db.password().isEmpty()) {
        if (error)
            *error = "A variável de ambiente ERP_DB_PASSWORD não foi definida.";
        return false;
    }

    if (!db.open()) {
        if (error)
            *error = db.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase Database::connection()
{
    return QSqlDatabase::database("erp_connection");
}
