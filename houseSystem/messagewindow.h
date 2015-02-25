#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
    class messageWindow;
}

class messageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit messageWindow(QWidget *parent = 0);
    ~messageWindow();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::messageWindow *ui;
};

#endif // MESSAGEWINDOW_H
