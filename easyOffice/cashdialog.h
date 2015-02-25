#ifndef CASHDIALOG_H
#define CASHDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
    class cashDialog;
}

class cashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cashDialog(QWidget *parent = 0);
    ~cashDialog();

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::cashDialog *ui;
};

#endif // CASHDIALOG_H
