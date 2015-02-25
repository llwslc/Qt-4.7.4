#ifndef TURNOVERSYSTEM_H
#define TURNOVERSYSTEM_H

#include <QMainWindow>
#include "function.h"
#include "keepersystem.h"
#include "servesystem.h"
#include "turnoversystem.h"

namespace Ui {
    class turnoverSystem;
}

class turnoverSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit turnoverSystem(QWidget *parent = 0);
    ~turnoverSystem();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::turnoverSystem *ui;
};

#endif // TURNOVERSYSTEM_H
