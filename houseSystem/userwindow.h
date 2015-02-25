#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "common.h"
#include "messagewindow.h"

namespace Ui {
class userWindow;
}

class userWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit userWindow(QWidget *parent = 0);
    ~userWindow();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    int picCol, picRow;

signals:
    void closeWindows();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::userWindow *ui;
    messageWindow messagew;
};

#endif // USERWINDOW_H
