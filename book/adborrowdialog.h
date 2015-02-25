#ifndef ADBORROWDIALOG_H
#define ADBORROWDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class adBorrowDialog;
}

class adBorrowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adBorrowDialog(QWidget *parent = 0);
    ~adBorrowDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void updateComboBox();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

private:
    Ui::adBorrowDialog *ui;
};

#endif // ADBORROWDIALOG_H
