#ifndef ADOVERDIALOG_H
#define ADOVERDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "chatdialog.h"

namespace Ui {
    class adOverDialog;
}

class adOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adOverDialog(QWidget *parent = 0);
    ~adOverDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void updateComboBox();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::adOverDialog *ui;
    ChatDialog chatw;
};

#endif // ADOVERDIALOG_H
