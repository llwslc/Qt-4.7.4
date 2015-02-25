#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();
    void paintEvent(QPaintEvent *);

    QSqlTableModel *currentTableModel;
    QTableView *currentView;
    int idNum;
    QString picPath;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_7_clicked();

private:
    Ui::adminDialog *ui;

    void comboBox_2DataFill(const int comboBoxIndex);
};

#endif // ADMINDIALOG_H
