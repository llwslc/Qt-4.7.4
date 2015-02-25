#ifndef BOOKSEARCHDIALOG_H
#define BOOKSEARCHDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class bookSearchDialog;
}

class bookSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bookSearchDialog(QWidget *parent = 0);
    ~bookSearchDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::bookSearchDialog *ui;
};

#endif // BOOKSEARCHDIALOG_H
