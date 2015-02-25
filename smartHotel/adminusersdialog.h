#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class adminUsersDialog;
}

class adminUsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminUsersDialog(QWidget *parent = 0);
    ~adminUsersDialog();

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
    Ui::adminUsersDialog *ui;
};

#endif // USERDIALOG_H
