#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "booksearchdialog.h"
#include "callsearchdialog.h"
#include "insearchdialog.h"

namespace Ui {
    class searchDialog;
}

class searchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchDialog(QWidget *parent = 0);
    ~searchDialog();

    bookSearchDialog bookw;
    callSearchDialog callw;
    inSearchDialog inw;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::searchDialog *ui;
};

#endif // SEARCHDIALOG_H
