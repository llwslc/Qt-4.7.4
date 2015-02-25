#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "clientdialog.h"
#include "goodsdialog.h"
#include "orderdialog.h"
#include "orderstatusdialog.h"
#include "pwddialog.h"

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::mainDialog *ui;
    clientDialog clientw;
    goodsDialog goodsw;
    orderDialog orderw;
    orderStatusDialog ordersw;
    pwdDialog pwdw;
};

#endif // MAINDIALOG_H
