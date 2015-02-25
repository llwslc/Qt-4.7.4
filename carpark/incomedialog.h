#ifndef INCOMEDIALOG_H
#define INCOMEDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class incomeDialog;
}

class incomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit incomeDialog(QWidget *parent = 0);
    ~incomeDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::incomeDialog *ui;
};

#endif // INCOMEDIALOG_H
