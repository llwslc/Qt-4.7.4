#ifndef WEIGHTDIALOG_H
#define WEIGHTDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class weightDialog;
}

class weightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit weightDialog(QWidget *parent = 0);
    ~weightDialog();
void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::weightDialog *ui;
};

#endif // WEIGHTDIALOG_H
