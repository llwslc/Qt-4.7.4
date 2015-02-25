#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "assessordialog.h"
#include "turnoverdialog.h"
#include "memberaddialog.h"
#include "userdialog.h"
#include "punchdialog.h"

namespace Ui {
    class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::adminDialog *ui;
    assessorDialog assw;
    turnoverDialog turnw;
    memberadDialog memw;
    userDialog userw;
    punchDialog punw;
};

#endif // ADMINDIALOG_H
