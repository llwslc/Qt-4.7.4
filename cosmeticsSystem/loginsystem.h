#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <QMainWindow>
#include "function.h"
#include "adminsystem.h"
#include "keepersystem.h"
#include "servesystem.h"
#include "turnoversystem.h"

namespace Ui {
    class loginSystem;
}

class loginSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginSystem(QWidget *parent = 0);
    ~loginSystem();

    void paintEvent(QPaintEvent *);

private slots:
    void on_cancelBut_clicked();

    void on_loginBut_clicked();

    void loginShow();

private:
    Ui::loginSystem *ui;
    adminSystem adWindow;
    keeperSystem kpWindow;
    serveSystem svWindow;
};

#endif // LOGINSYSTEM_H
