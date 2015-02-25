#ifndef SERVEWINDOW_H
#define SERVEWINDOW_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
    class serveWindow;
}

class serveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit serveWindow(QWidget *parent = 0);
    ~serveWindow();

    QList<QTableView*> tabViews;
    QStringList sqlNames;
    QString sqlName;

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    int currentIndexNum;

    QSqlTableModel *tempTableModel;
    QTableView *tempView;

    bool currentModelDoubleClickedFlag;
    int currentModelDoubleClickedRow;
    int currentModelDoubleClickedColumn;

    QString deskNumMoneySum;

private slots:
    void on_svPayButton_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_svPwdButton_clicked();
    void on_svSelButton_clicked();
    void on_svSubButton_clicked();
    void on_svChButton_clicked();
    void on_svDelButton_clicked();
    void on_svAddButton_clicked();
    void on_svTableAction_triggered();

    void on_svDishesAction_triggered();

    void on_svPayAction_triggered();

    void on_svPwdAction_triggered();

    void on_svCancelAction_triggered();

    void on_svDishesTabView_doubleClicked(const QModelIndex &index);

    void addDeskDishesToDatabass(const QModelIndex &index);

    void on_svTabNumEdit_selectionChanged();

private:
    Ui::serveWindow *ui;
};

#endif // SERVEWINDOW_H
