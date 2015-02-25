#ifndef ADMINSYSTEM_H
#define ADMINSYSTEM_H

#include <QMainWindow>
#include "function.h"
#include "adminsystem.h"
#include "keepersystem.h"
#include "servesystem.h"
#include "turnoversystem.h"

namespace Ui {
class adminSystem;
}

class adminSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminSystem(QWidget *parent = 0);
    ~adminSystem();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    int tagFlag;

    void paintEvent(QPaintEvent *);

signals:
    void exitLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_12_clicked();

private:
    Ui::adminSystem *ui;
    turnoverSystem tWindows;
};

#endif // ADMINSYSTEM_H
