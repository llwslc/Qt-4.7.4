#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "common.h"
#include "addressdialog.h"
#include "smsdialog.h"
#include "userdialog.h"
#include "aboutdialog.h"
#include "groupdialog.h"
#include "qexcel.h"
#include "sgroupdialog.h"

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    addressDialog addw;
    smsDialog smsw;
    userDialog userw;
    aboutDialog aboutw;
    groupDialog groupw;
    sgroupDialog sgroupw;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
