#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "func.h"
#include "roompreviewdialog.h"
#include "checkindialog.h"
#include "staffdialog.h"
#include "memberdialog.h"
#include "accountdialog.h"

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::mainDialog *ui;
    roomPreviewDialog roompreDlg;
    checkinDialog checkinDlg;
    staffDialog staffDlg;
    memberDialog memberDlg;
    accountDialog accountDlg;
};

#endif // MAINDIALOG_H
