#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include "myFunc.h"

namespace Ui {
    class passwordDialog;
}

class passwordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit passwordDialog(QWidget *parent = 0);
    ~passwordDialog();

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::passwordDialog *ui;
};

#endif // PASSWORDDIALOG_H
