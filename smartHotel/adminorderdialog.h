#ifndef ADMINORDERDIALOG_H
#define ADMINORDERDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class adminOrderDialog;
}

class adminOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminOrderDialog(QWidget *parent = 0);
    ~adminOrderDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void initGuest();

    void initRoom();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &date);

private:
    Ui::adminOrderDialog *ui;
};

#endif // ADMINORDERDIALOG_H
