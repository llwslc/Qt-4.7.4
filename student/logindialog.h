#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "maindialog.h"

namespace Ui {
    class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::loginDialog *ui;
    mainDialog mainw;
};

#endif // LOGINDIALOG_H
