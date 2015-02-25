#ifndef ADBOOKDIALOG_H
#define ADBOOKDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "admodifybookdialog.h"

namespace Ui {
    class adBookDialog;
}

class adBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adBookDialog(QWidget *parent = 0);
    ~adBookDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

signals:
    void addBook();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::adBookDialog *ui;
    adModifyBookDialog adModifyBookw;
};

#endif // ADBOOKDIALOG_H
