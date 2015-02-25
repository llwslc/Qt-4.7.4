#ifndef ADMINGUESTSDIALOG_H
#define ADMINGUESTSDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class adminGuestsDialog;
}

class adminGuestsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminGuestsDialog(QWidget *parent = 0);
    ~adminGuestsDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void modGuest();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

private:
    Ui::adminGuestsDialog *ui;
};

#endif // ADMINGUESTSDIALOG_H
