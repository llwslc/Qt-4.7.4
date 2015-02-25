#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class addressDialog;
}

class addressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addressDialog(QWidget *parent = 0);
    ~addressDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString picPath;

    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

signals:
    void addUser();

private slots:

    void initComboBox_2();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::addressDialog *ui;
};

#endif // ADDRESSDIALOG_H
