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
#include "coursedialog.h"
#include "scoredialog.h"
#include "studialog.h"
#include "subjectdialog.h"
#include "userdialog.h"
#include "common.h"

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
    courseDialog courw;
    scoreDialog scow;
    stuDialog stuw;
    subjectDialog subw;
    userDialog userw;
};

#endif // MAINDIALOG_H
