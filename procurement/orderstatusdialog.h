#ifndef ORDERSTATUSDIALOG_H
#define ORDERSTATUSDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class orderStatusDialog;
}

class orderStatusDialog : public QDialog
{
    Q_OBJECT

public:
    explicit orderStatusDialog(QWidget *parent = 0);
    ~orderStatusDialog();

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::orderStatusDialog *ui;
};

#endif // ORDERSTATUSDIALOG_H
