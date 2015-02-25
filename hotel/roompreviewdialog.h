#ifndef ROOMPREVIEWDIALOG_H
#define ROOMPREVIEWDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class roomPreviewDialog;
}

class roomPreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit roomPreviewDialog(QWidget *parent = 0);
    ~roomPreviewDialog();

    QSqlRelationalTableModel *currentTableModel;
    QTableView *currentView;

    int picCol, picRow;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::roomPreviewDialog *ui;
};

#endif // ROOMPREVIEWDIALOG_H
