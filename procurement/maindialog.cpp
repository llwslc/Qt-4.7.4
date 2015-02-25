#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::on_pushButton_clicked()
{
    //客户基本信息
    clientw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //订单基本信息
    orderw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //订单状态信息
    ordersw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //产品基本信息
    goodsw.show();
}

void mainDialog::on_pushButton_5_clicked()
{
    //密码修改
    pwdw.show();
}

void mainDialog::on_pushButton_6_clicked()
{
    //退出
    this->close();
}
