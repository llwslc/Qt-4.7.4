#ifndef STAFFDIALOG_H
#define STAFFDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
class staffDialog;
}

class staffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit staffDialog(QWidget *parent = 0);
    ~staffDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString picPath;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::staffDialog *ui;
};

#endif // STAFFDIALOG_H
