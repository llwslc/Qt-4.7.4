#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class scoreDialog;
}

class scoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit scoreDialog(QWidget *parent = 0);
    ~scoreDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::scoreDialog *ui;
};

#endif // SCOREDIALOG_H
