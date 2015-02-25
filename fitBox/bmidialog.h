#ifndef BMIDIALOG_H
#define BMIDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class bmiDialog;
}

class bmiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bmiDialog(QWidget *parent = 0);
    ~bmiDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::bmiDialog *ui;
};

#endif // BMIDIALOG_H
