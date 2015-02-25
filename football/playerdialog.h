#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include "mysqldata.h"

namespace Ui {
class playerDialog;
}

class playerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit playerDialog(QWidget *parent = 0);
    ~playerDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    QString picPath;

    void paintEvent(QPaintEvent *);

signals:
    void addPlayer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::playerDialog *ui;
};

#endif // PLAYERDIALOG_H
