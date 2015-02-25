#ifndef LOGONDIALOG_H
#define LOGONDIALOG_H

#include <QDialog>
#include "common.h"
#include "maindialog.h"

namespace Ui {
    class logonDialog;
}

class logonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logonDialog(QWidget *parent = 0);
    ~logonDialog();

    void paintEvent(QPaintEvent *);

    mainDialog mainw;

private slots:
    void on_loginBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::logonDialog *ui;
};

#endif // LOGONDIALOG_H
