#ifndef STUIDDIALOG_H
#define STUIDDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class stuidDialog;
}

class stuidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stuidDialog(QWidget *parent = 0);
    ~stuidDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::stuidDialog *ui;
};

#endif // STUIDDIALOG_H
