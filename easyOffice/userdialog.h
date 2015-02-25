#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "myfunc.h"

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
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_3_clicked();

private:
    Ui::userDialog *ui;
};

#endif // USERDIALOG_H
