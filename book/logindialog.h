#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "adminDialog.h"
#include "userDialog.h"

namespace Ui {
    class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

private slots:
    void loginShow();

    void on_loginBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::loginDialog *ui;
    adminDialog adminw;
    userDialog userw;
};

#endif // LOGINDIALOG_H
