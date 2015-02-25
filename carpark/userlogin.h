#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QMainWindow>
#include "common.h"
#include "maindialog.h"

namespace Ui {
    class userlogin;
}

class userlogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit userlogin(QWidget *parent = 0);
    ~userlogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::userlogin *ui;
    mainDialog mainw;
};

#endif // USERLOGIN_H
