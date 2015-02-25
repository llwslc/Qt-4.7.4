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
#include "checkindialog.h"
#include "incomedialog.h"
#include "roomdialog.h"
#include "searchdialog.h"

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

private:
    Ui::mainDialog *ui;
    checkinDialog checkinw;
    incomeDialog incomew;
    roomDialog roomw;
    searchDialog searchw;
};

#endif // MAINDIALOG_H
