#ifndef MATCHDIALOG_H
#define MATCHDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
    class matchDialog;
}

class matchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit matchDialog(QWidget *parent = 0);
    ~matchDialog();

    QSqlTableModel *currentTableModel_1;
    QSqlTableModel *currentTableModel_2;
    QTableView *currentView_1;
    QTableView *currentView_2;

    QString picPath;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_dateEdit_2_dateChanged(const QDate &date);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_label_2_linkActivated(const QString &link);

private:
    Ui::matchDialog *ui;
};

#endif // MATCHDIALOG_H
