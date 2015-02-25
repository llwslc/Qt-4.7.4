#include "userlogin.h"
#include "ui_userlogin.h"

userlogin::userlogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userlogin)
{
    ui->setupUi(this);
}

userlogin::~userlogin()
{
    delete ui;
}

void userlogin::on_pushButton_clicked()
{
    //登录
    QSqlQuery query;

    query.exec("select * from person where name = '" + ui->lineEdit->text().trimmed()
               + "' and passwd = '"+ ui->lineEdit_2->text() + "'");

    if (query.next())
    {
        this->close();
        mainw.show();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

        ui->lineEdit->clear();      //清空用户名输入框
        ui->lineEdit_2->clear();       //清空密码输入框
        ui->lineEdit->setFocus();   //将光标转到用户名输入框
    }
}

void userlogin::on_pushButton_2_clicked()
{
    //取消
}
