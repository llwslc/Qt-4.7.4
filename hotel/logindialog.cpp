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

void loginDialog::on_pushButton_clicked()
{
    //登录
    QSqlQuery query;

    query.exec("select * from user where name = '" + ui->lineEdit->text().trimmed()
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

void loginDialog::on_pushButton_2_clicked()
{
    //取消
    close();
}
