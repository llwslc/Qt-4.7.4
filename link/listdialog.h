#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class listDialog;
}

class listDialog : public QDialog
{
    Q_OBJECT

public:
    explicit listDialog(QWidget *parent = 0);
    ~listDialog();    

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::listDialog *ui;
};

#endif // LISTDIALOG_H
