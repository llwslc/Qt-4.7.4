#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "inroomdialog.h"
#include "outroomdialog.h"
#include "bookroomdialog.h"

namespace Ui {
class checkinDialog;
}

class checkinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit checkinDialog(QWidget *parent = 0);
    ~checkinDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    inroomDialog inroomw;
    outroomDialog outroomw;
    bookroomDialog bookroomw;

    void showEvent(QShowEvent *);

signals:
    void modifyCheckIn();

private slots:
    void initDialog();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::checkinDialog *ui;
};

#endif // CHECKINDIALOG_H
