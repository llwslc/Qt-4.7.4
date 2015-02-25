#ifndef RANDOMDIALOG_H
#define RANDOMDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
    class randomDialog;
}

class randomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit randomDialog(QWidget *parent = 0);
    ~randomDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::randomDialog *ui;
};

#endif // RANDOMDIALOG_H
