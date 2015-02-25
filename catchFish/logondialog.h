#ifndef LOGONDIALOG_H
#define LOGONDIALOG_H

#include <QDialog>
#include "common.h"
#include "fishdialog.h"

namespace Ui {
    class logonDialog;
}

class logonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logonDialog(QWidget *parent = 0);
    ~logonDialog();

    fishDialog w;

private slots:
    void on_loginBut_clicked();

    void on_cancelBut_clicked();

    void on_registerBut_clicked();

private:
    Ui::logonDialog *ui;
};

#endif // LOGONDIALOG_H
