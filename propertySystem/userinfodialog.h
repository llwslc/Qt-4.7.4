#ifndef USERINFODIALOG_H
#define USERINFODIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class userinfoDialog;
}

class userinfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userinfoDialog(QWidget *parent = 0);
    ~userinfoDialog();

    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

private:
    Ui::userinfoDialog *ui;
};

#endif // USERINFODIALOG_H
