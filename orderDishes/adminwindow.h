#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <common.h>

namespace Ui {
    class adminWindow;
}

class adminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminWindow(QWidget *parent = 0);
    ~adminWindow();

    QList<QTableView*> tabViews;
    QStringList sqlNames;
    QString sqlName;

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    int currentIndexNum;

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_adSubButton_clicked();
    void on_adDishesAction_triggered();

    void on_adPeopleAction_triggered();

    void on_adOrderAction_triggered();

    void on_adDayAction_triggered();

    void on_adMonthAction_triggered();

    void on_adDateAction_triggered();

    void on_adPwdAction_triggered();

    void on_adCancelAction_triggered();

    void on_adAddButton_clicked();

    void on_adDelButton_clicked();

    void on_adChButton_clicked();

    void on_adSelButton_clicked();

    void on_adPwdButton_clicked();

private:
    Ui::adminWindow *ui;
};

#endif // ADMINWINDOW_H
