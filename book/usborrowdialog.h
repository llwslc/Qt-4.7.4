#ifndef USBORROWDIALOG_H
#define USBORROWDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class usBorrowDialog;
}

class usBorrowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit usBorrowDialog(QWidget *parent = 0);
    ~usBorrowDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

    QString stuCode;

    void setStuCode(QString);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::usBorrowDialog *ui;
};

#endif // USBORROWDIALOG_H
