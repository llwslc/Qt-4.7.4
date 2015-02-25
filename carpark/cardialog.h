#ifndef CARDIALOG_H
#define CARDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class carDialog;
}

class carDialog : public QDialog
{
    Q_OBJECT

public:
    explicit carDialog(QWidget *parent = 0);
    ~carDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString selectCarId;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_checkBox_clicked();

private:
    Ui::carDialog *ui;
};

#endif // CARDIALOG_H
