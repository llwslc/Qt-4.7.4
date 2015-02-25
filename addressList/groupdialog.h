#ifndef GROUPDIALOG_H
#define GROUPDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class groupDialog;
}

class groupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit groupDialog(QWidget *parent = 0);
    ~groupDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

signals:
    void addGroup();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::groupDialog *ui;
};

#endif // GROUPDIALOG_H
