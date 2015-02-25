#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "adminwindow.h"
#include "userwindow.h"
#include "common.h"

namespace Ui {
    class loginWindow;
}

class loginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = 0);
    ~loginWindow();

private slots:
    void on_cancelBut_clicked();

    void on_loginBut_clicked();

    void showLoginWindow();

private:
    Ui::loginWindow *ui;
    adminWindow adWindow;
    userWindow usWindow;
};

#endif // LOGINWINDOW_H
