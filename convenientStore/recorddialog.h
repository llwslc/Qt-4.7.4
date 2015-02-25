#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class recordDialog;
}

class recordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit recordDialog(QWidget *parent = 0);
    ~recordDialog();

    void showEvent(QShowEvent *event);

    int mScore;

private slots:
    void on_pushButton_clicked();

private:
    Ui::recordDialog *ui;
};

#endif // RECORDDIALOG_H
