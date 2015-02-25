#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "myFunc.h"
#include "wardrobewindow.h"
#include "staffdialog.h"

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
    wardrobeWindow wardrobew;
    staffDialog staffw;
};

#endif // LOGINDIALOG_H
