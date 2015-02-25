#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include "common.h"

namespace Ui {
    class courseDialog;
}

class courseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit courseDialog(QWidget *parent = 0);
    ~courseDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::courseDialog *ui;
};

#endif // COURSEDIALOG_H
