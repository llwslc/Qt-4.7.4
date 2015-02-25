#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "func.h"
#include "mainwindow.h"

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
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::loginDialog *ui;
    mainWindow mainw;
};

#endif // LOGINDIALOG_H
