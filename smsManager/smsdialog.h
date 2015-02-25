#ifndef SMSDIALOG_H
#define SMSDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class smsDialog;
}

class smsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit smsDialog(QWidget *parent = 0);
    ~smsDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

    void initCombobox();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::smsDialog *ui;
};

#endif // SMSDIALOG_H
