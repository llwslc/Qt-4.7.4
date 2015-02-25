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
#include "admindialog.h"
#include "waiterdialog.h"

namespace Ui {
    class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::loginDialog *ui;
    adminDialog adminw;
    waiterDialog waiterw;
};

#endif // LOGINDIALOG_H
