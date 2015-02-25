#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include "mysqldata.h"

namespace Ui {
    class gameDialog;
}

class gameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit gameDialog(QWidget *parent = 0);
    ~gameDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

signals:
    void addGame();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::gameDialog *ui;
};

#endif // GAMEDIALOG_H
