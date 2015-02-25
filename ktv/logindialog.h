#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "function.h"
#include "adminwidget.h"
#include "serverwidget.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

    void paintEvent(QPaintEvent *);

signals:
    void returnDialog();

private slots:
    void returnShow();

    void on_cancelBut_clicked();

    void on_loginBut_clicked();

    void on_cancelBut_2_clicked();

private:
    Ui::loginDialog *ui;
    adminWidget adminw;
    serverWidget serverw;
};

#endif // LOGINDIALOG_H
