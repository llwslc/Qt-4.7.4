#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "common.h"
#include "borrowdialog.h"
#include "backdialog.h"
#include "goodsdialog.h"
#include "stockadddialog.h"
#include "stockmoddialog.h"
#include "stockSelDialog.h"

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

signals:
    void OnClose();

    void OnExit();

private slots:
    void selfShow();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::mainDialog *ui;
    borrowDialog borrowW;
    backDialog backW;
    goodsDialog goodsW;
    stockAddDialog addW;
    stockModDialog modW;
    stockSelDialog selW;
};

#endif // MAINDIALOG_H
