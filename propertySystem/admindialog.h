#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "cardialog.h"
#include "ownerdialog.h"

namespace Ui {
    class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    int tableSeletc;

    void addComboBoxItem();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

private:
    Ui::adminDialog *ui;
    carDialog carw;
    ownerDialog ownerw;
};

#endif // ADMINDIALOG_H
