#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_loginBut_clicked()
{
    //登录
    QSqlQuery query;
    QString sql;

    if (ui->adminRadio->isChecked() == true)
    {
        sql = "select * from users where name = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 0";
        query.exec(sql);

        if (query.next())
        {
            loginName = ui->nameEdit->text().trimmed();
            this->close();
            wardrobew.show();

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
        sql = "select * from users where name = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 1";
        query.exec(sql);

        if (query.next())
        {
            loginName = ui->nameEdit->text().trimmed();
            this->close();
            staffw.show();

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

void loginDialog::on_cancelBut_clicked()
{
    //退出
    this->close();
}

void loginDialog::loginShow()
{
    //登录对话框显示
    this->show();

    ui->nameEdit->clear();      //清空用户名输入框
    ui->pwdEdit->clear();       //清空密码输入框
    ui->nameEdit->setFocus();   //将光标转到用户名输入框
}
