#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "cardialog.h"
#include "goodsdialog.h"
#include "ordersdialog.h"
#include "userdialog.h"

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::mainDialog *ui;
    carDialog carw;
    goodsDialog goodw;
    ordersDialog ordersw;
    userDialog userw;
};

#endif // MAINDIALOG_H
