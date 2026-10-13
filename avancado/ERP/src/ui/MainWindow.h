#pragma once

#include <QMainWindow>

class QTabWidget;
class QTableView;
class QSqlTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void addTableTab(
        const QString &title,
        const QString &tableName
    );

    QTabWidget *tabs_ = nullptr;
};