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
    //地址簿
    addw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //信息管理
    smsw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //人员管理
    userw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //关于
    aboutw.show();
}
