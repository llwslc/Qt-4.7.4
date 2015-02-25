#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "common.h"
#include "userdialog.h"


namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    userDialog userw;

private slots:

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
