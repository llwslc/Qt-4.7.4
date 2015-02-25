#ifndef KEEPERSYSTEM_H
#define KEEPERSYSTEM_H

#include <QMainWindow>
#include "function.h"
#include "keepersystem.h"
#include "servesystem.h"
#include "turnoversystem.h"

namespace Ui {
    class keeperSystem;
}

class keeperSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit keeperSystem(QWidget *parent = 0);
    ~keeperSystem();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

signals:
    void exitLogin();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::keeperSystem *ui;
};

#endif // KEEPERSYSTEM_H
