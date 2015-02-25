#ifndef ADMINROOMSDIALOG_H
#define ADMINROOMSDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class adminRoomsDialog;
}

class adminRoomsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminRoomsDialog(QWidget *parent = 0);
    ~adminRoomsDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

signals:
    void modRoom();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::adminRoomsDialog *ui;
};

#endif // ADMINROOMSDIALOG_H
