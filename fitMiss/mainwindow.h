#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "func.h"
#include "admindialog.h"
#include "bmidialog.h"
#include "caloriedialog.h"
#include "sizedialog.h"
#include "stdweightdialog.h"
#include "recorddialog.h"
#include "historydialog.h"
#include "weightdialog.h"
#include "passworddialog.h"

namespace Ui {
    class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_2_clicked(const QModelIndex &index);

    void on_tableWidget_4_clicked(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_pushButton_12_clicked();

private:
    Ui::mainWindow *ui;

    void foodItemUpdate();
    void cookbookItemUpdate();
    void sportsItemUpdate();

    bmiDialog *bmiDlg;
    calorieDialog *calDlg;
    sizeDialog *sizeDlg;
    stdweightDialog *stdwDlg;
    adminDialog adminDlg;
    recordDialog recDlg;
    weightDialog weiDlg;
    historyDialog hisDlg;
    passwordDialog pwdDlg;
};

#endif // MAINWINDOW_H
