#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class memberDialog;
}

class memberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit memberDialog(QWidget *parent = 0);
    ~memberDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::memberDialog *ui;
};

#endif // MEMBERDIALOG_H
