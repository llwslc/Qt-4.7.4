#ifndef WARDROBEWINDOW_H
#define WARDROBEWINDOW_H

#include <QWidget>
#include "myfunc.h"
#include "wardrobeDialog.h"
#include "cashdialog.h"
#include "userDialog.h"

namespace Ui {
    class wardrobeWindow;
}

class wardrobeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit wardrobeWindow(QWidget *parent = 0);
    ~wardrobeWindow();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void tableWidgetData();

    bool clothesSelect; //¥Ó≈‰±Í÷æ
    int clothesSelectId; //—°‘ÒID∫≈
    QString picPath;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

private:
    Ui::wardrobeWindow *ui;
    wardrobeDialog warw;
    cashDialog cashw;
    userDialog userw;
};

#endif // WARDROBEWINDOW_H
