#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mydatabase.h"
#include "hoteldialog.h"
#include "placedialog.h"
#include "mapdialog.h"
#include "userdialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    hotelDialog hotelw;
    placeDialog placew;
    mapDialog mapw;
    userDialog userw;
};

#endif // MAINWINDOW_H
