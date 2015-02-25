#ifndef LIBROOMDIALOG_H
#define LIBROOMDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class libroomDialog;
}

class libroomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit libroomDialog(QWidget *parent = 0);
    ~libroomDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
signals:
    void modifyLib();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::libroomDialog *ui;
};

#endif // LIBROOMDIALOG_H
