#ifndef WAITERDIALOG_H
#define WAITERDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "memberdialog.h"
#include "cashdialog.h"
#include "spacedialog.h"

namespace Ui {
    class waiterDialog;
}

class waiterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit waiterDialog(QWidget *parent = 0);
    ~waiterDialog();

    QString name;
    QString logtime;

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::waiterDialog *ui;
    memberDialog memw;
    cashDialog cashw;
    spaceDialog spacew;
};

#endif // WAITERDIALOG_H
