#ifndef DIALOG_H
#define DIALOG_H

#include "common.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void init();

    int selectClass;

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_level_currentIndexChanged(const QString &arg1);

    void on_comboBox_type_currentIndexChanged(const QString &arg1);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
