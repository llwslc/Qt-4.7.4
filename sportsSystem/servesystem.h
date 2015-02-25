#ifndef SERVESYSTEM_H
#define SERVESYSTEM_H

#include <QMainWindow>
#include "function.h"
#include "keepersystem.h"
#include "servesystem.h"
#include "turnoversystem.h"

namespace Ui {
    class serveSystem;
}

class serveSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit serveSystem(QWidget *parent = 0);
    ~serveSystem();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    int sumPrice;

    QString todayDate; //结算日期
    QString startTime; //结算时间

    QString punchLoginDateTime; //打卡时间
    QString punchOutDateTime;   //退出打卡

    void paintEvent(QPaintEvent *);

signals:
    void exitLogin();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::serveSystem *ui;
};

#endif // SERVESYSTEM_H
