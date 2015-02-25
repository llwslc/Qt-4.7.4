#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "adbookdialog.h"
#include "adborrowdialog.h"
#include "adstudialog.h"
#include "adoverdialog.h"
#include "booksearchdialog.h"

namespace Ui {
    class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();

signals:
    void loginOut();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::adminDialog *ui;
    adBookDialog adBookw;
    adBorrowDialog adBorroww;
    adStuDialog adStuw;
    adOverDialog adOverw;
    bookSearchDialog bookSearchw;
};

#endif // ADMINDIALOG_H
