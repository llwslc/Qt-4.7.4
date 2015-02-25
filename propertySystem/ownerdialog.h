#ifndef OWNERDIALOG_H
#define OWNERDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class ownerDialog;
}

class ownerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ownerDialog(QWidget *parent = 0);
    ~ownerDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString selectid;

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::ownerDialog *ui;
};

#endif // OWNERDIALOG_H
