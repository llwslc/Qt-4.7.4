#ifndef GOODSDIALOG_H
#define GOODSDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class goodsDialog;
}

class goodsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit goodsDialog(QWidget *parent = 0);
    ~goodsDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::goodsDialog *ui;
};

#endif // GOODSDIALOG_H
