#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class accountDialog;
}

class accountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit accountDialog(QWidget *parent = 0);
    ~accountDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::accountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
