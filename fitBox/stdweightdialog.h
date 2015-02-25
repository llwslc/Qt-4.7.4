#ifndef STDWEIGHTDIALOG_H
#define STDWEIGHTDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class stdweightDialog;
}

class stdweightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stdweightDialog(QWidget *parent = 0);
    ~stdweightDialog();
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::stdweightDialog *ui;
};

#endif // STDWEIGHTDIALOG_H
