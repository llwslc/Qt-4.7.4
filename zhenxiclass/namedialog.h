#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class nameDialog;
}

class nameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit nameDialog(QWidget *parent = 0);
    ~nameDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::nameDialog *ui;
};

#endif // NAMEDIALOG_H
