#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QMessageBox>
#include "colorDialog.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    colorDialog colorDlg;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
