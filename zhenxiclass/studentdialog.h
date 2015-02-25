#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class studentDialog;
}

class studentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit studentDialog(QWidget *parent = 0);
    ~studentDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString picPath;

    void paintEvent(QPaintEvent *);

signals:
    void addUser();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::studentDialog *ui;
};

#endif // ADDRESSDIALOG_H
