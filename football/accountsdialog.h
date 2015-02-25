#ifndef ACCOUNTSDIALOG_H
#define ACCOUNTSDIALOG_H

#include <QDialog>
#include "mysqldata.h"

namespace Ui {
class accountsDialog;
}

class accountsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit accountsDialog(QWidget *parent = 0);
    ~accountsDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::accountsDialog *ui;
};

#endif // ACCOUNTSDIALOG_H
