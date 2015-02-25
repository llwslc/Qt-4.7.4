#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "userinfodialog.h"

namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = 0);
    ~userDialog();

    QSqlTableModel *currentTableModel_1;
    QTableView *currentView_1;
    QSqlTableModel *currentTableModel_2;
    QTableView *currentView_2;

    void showEvent(QShowEvent *event);

    void paintEvent(QPaintEvent *);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:
    Ui::userDialog *ui;
    userinfoDialog infow;
};

#endif // USERDIALOG_H
