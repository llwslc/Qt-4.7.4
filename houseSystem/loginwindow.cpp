#include "loginwindow.h"
#include "ui_loginwindow.h"

loginWindow::loginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);

    connect(&adWindow, SIGNAL(closeWindows()), this, SLOT(showLoginWindow()));
    connect(&usWindow, SIGNAL(closeWindows()), this, SLOT(showLoginWindow()));
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_cancelBut_clicked()
{
    close();
}

void loginWindow::on_loginBut_clicked()
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
            adminname = ui->nameEdit->text().trimmed();
            this->close();
            adWindow.show();

            ui->nameEdit->clear();      //清空用户名输入框
            ui->pwdEdit->clear();       //清空密码输入框
            ui->nameEdit->setFocus();   //将光标转到用户名输入框
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->nameEdit->clear();      //清空用户名输入框
            ui->pwdEdit->clear();       //清空密码输入框
            ui->nameEdit->setFocus();   //将光标转到用户名输入框

        }
    }
    if (ui->userRadio->isChecked() == true)
    {
        sql = "select * from person where pname = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 1";
        query.exec(sql);

        if (query.next())
        {
            username = ui->nameEdit->text().trimmed();
            this->close();
            usWindow.show();

            ui->nameEdit->clear();      //清空用户名输入框
            ui->pwdEdit->clear();       //清空密码输入框
            ui->nameEdit->setFocus();   //将光标转到用户名输入框
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

void loginWindow::showLoginWindow()
{
    this->show();
}
