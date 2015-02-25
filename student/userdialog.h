#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = 0);
    ~userDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::userDialog *ui;
};

#endif // USERDIALOG_H
