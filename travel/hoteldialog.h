#ifndef HOTELDIALOG_H
#define HOTELDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class hotelDialog;
}

class hotelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit hotelDialog(QWidget *parent = 0);
    ~hotelDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::hotelDialog *ui;
};

#endif // HOTELDIALOG_H
