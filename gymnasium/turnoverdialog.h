#ifndef TURNOVERDIALOG_H
#define TURNOVERDIALOG_H

#include <QDialog>
#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class turnoverDialog;
}

class turnoverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit turnoverDialog(QWidget *parent = 0);
    ~turnoverDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::turnoverDialog *ui;
};

#endif // TURNOVERDIALOG_H
