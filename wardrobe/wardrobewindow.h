#ifndef WARDROBEWINDOW_H
#define WARDROBEWINDOW_H

#include <QWidget>
#include "myfunc.h"
#include "matchDialog.h"
#include "randomdialog.h"
#include "wardrobedialog.h"
#include "cashdialog.h"

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

    bool clothesSelect; //衣服搭配标志
    int clothesSelectId; //衣服选择ID号
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

private:
    Ui::wardrobeWindow *ui;
    matchDialog matchDlg;
    randomDialog randDlg;
    wardrobeDialog warw;
    cashDialog cashw;
};

#endif // WARDROBEWINDOW_H
