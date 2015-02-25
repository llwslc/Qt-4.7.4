#ifndef PWDDIALOG_H
#define PWDDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class pwdDialog;
}

class pwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit pwdDialog(QWidget *parent = 0);
    ~pwdDialog();

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::pwdDialog *ui;
};

#endif // PWDDIALOG_H
