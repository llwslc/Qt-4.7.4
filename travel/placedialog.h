#ifndef PLACEDIALOG_H
#define PLACEDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class placeDialog;
}

class placeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit placeDialog(QWidget *parent = 0);
    ~placeDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString picPath;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::placeDialog *ui;
};

#endif // PLACEDIALOG_H
