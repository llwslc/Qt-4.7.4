#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class orderDialog;
}

class orderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit orderDialog(QWidget *parent = 0);
    ~orderDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::orderDialog *ui;
};

#endif // ORDERDIALOG_H
