#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include <QMainWindow>
#include "mydatabase.h"
#include "common.h"

namespace Ui {
    class itemWindow;
}

class itemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit itemWindow(QWidget *parent = 0);
    ~itemWindow();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::itemWindow *ui;

    void closeEvent(QCloseEvent *e);

    void fillTable();
    int dayid;
    int noteid;
};

#endif // ITEMWINDOW_H
