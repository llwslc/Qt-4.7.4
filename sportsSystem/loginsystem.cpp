#include "loginsystem.h"
#include "ui_loginsystem.h"

loginSystem::loginSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginSystem)
{
    ui->setupUi(this);

    connect(&adWindow, SIGNAL(exitLogin()), this, SLOT(loginShow()));
    connect(&kpWindow, SIGNAL(exitLogin()), this, SLOT(loginShow()));
    connect(&svWindow, SIGNAL(exitLogin()), this, SLOT(loginShow()));
}

loginSystem::~loginSystem()
{
    delete ui;
}

void loginSystem::on_cancelBut_clicked()
{
    close();
}

void loginSystem::on_loginBut_clicked()
{
    QSqlQuery query;
    QString sql;

    if (ui->adminRadio->isChecked() == true)
    {
        sql = "select * from person where pname = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 0";
        query.exec(sql);

        if (query.next())
        {
            this->close();
            adWindow.show();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->nameEdit->clear();      //清空用户名输入框
            ui->pwdEdit->clear();       //清空密码输入框
            ui->nameEdit->setFocus();   //将光标转到用户名输入框

        }
    }
    if (ui->serveRadio->isChecked() == true)
    {
        sql = "select * from person where pname = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 1";
        query.exec(sql);

        if (query.next())
        {
            serveName = ui->nameEdit->text().trimmed();
            this->close();
            svWindow.show();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->nameEdit->clear();      //清空用户名输入框
            ui->pwdEdit->clear();       //清空密码输入框
            ui->nameEdit->setFocus();   //将光标转到用户名输入框
        }
    }
    if (ui->keeperRadio->isChecked() == true)
    {
        sql = "select * from person where pname = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 2";
        query.exec(sql);

        if (query.next())
        {
            this->close();
            kpWindow.show();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->nameEdit->clear();      //清空用户名输入框
            ui->pwdEdit->clear();       //清空密码输入框
            ui->nameEdit->setFocus();   //将光标转到用户名输入框
        }
    }
}

void loginSystem::loginShow()
{
    //显示登录框
    this->show();
}

void loginSystem::paintEvent(QPaintEvent *)
{
    //背景图片
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/3.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
