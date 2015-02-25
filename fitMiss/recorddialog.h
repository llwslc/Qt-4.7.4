#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class recordDialog;
}

class recordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit recordDialog(QWidget *parent = 0);
    ~recordDialog();
    void paintEvent(QPaintEvent *);

    QSqlTableModel *currentTableModel_1;
    QSqlTableModel *currentTableModel_2;
    QTableView *currentView_1;
    QTableView *currentView_2;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

private:
    Ui::recordDialog *ui;
};

#endif // RECORDDIALOG_H
