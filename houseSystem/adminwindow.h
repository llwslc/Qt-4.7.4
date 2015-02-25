#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
class adminWindow;
}

class adminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminWindow(QWidget *parent = 0);
    ~adminWindow();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

signals:
    void closeWindows();

private slots:
    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_26_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_27_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_tableView_4_clicked(const QModelIndex &index);

    void on_tableView_5_clicked(const QModelIndex &index);

    void on_tableView_6_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_tableView_3_doubleClicked(const QModelIndex &index);

    void on_tableView_4_doubleClicked(const QModelIndex &index);

    void on_tableView_5_doubleClicked(const QModelIndex &index);

    void on_tableView_6_doubleClicked(const QModelIndex &index);

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_35_clicked();

    void on_tableView_7_clicked(const QModelIndex &index);

    void on_action_7_triggered();

    void on_action_8_triggered();

private:
    Ui::adminWindow *ui;
};

#endif // ADMINWINDOW_H
