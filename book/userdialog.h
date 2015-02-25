#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "usborrowdialog.h"
#include "usinfodialog.h"
#include "booksearchdialog.h"
#include "chatdialog.h"

namespace Ui {
    class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = 0);
    ~userDialog();

    QTimer *msgTimer;

    QString stuCode;

    void setStuCode(QString);

    void showEvent(QShowEvent *);

    void closeEvent(QCloseEvent *);

signals:
    void loginOut();

private slots:
    void msgTimeOut();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::userDialog *ui;
    usBorrowDialog usBorroww;
    usInfoDialog usInfow;
    bookSearchDialog bookSearchw;
    ChatDialog chatw;
};

#endif // USERDIALOG_H
