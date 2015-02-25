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
    //信息管理
    stuw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //人员管理
    userw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //身份证查询
    idnumw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //监护人查询
    stuidw.show();
}

void mainDialog::on_pushButton_5_clicked()
{
    //姓名查询
    namew.show();
}

void mainDialog::on_pushButton_6_clicked()
{
    //电话查询
    phonew.show();
}
