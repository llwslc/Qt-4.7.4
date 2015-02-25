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
    //学生信息管理
    stuw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //实验室管理
    libw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //课程信息管理
    subw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //实验室预约
    libtimew.show();
}

void mainDialog::on_pushButton_6_clicked()
{
    //登录人员管理
    userw.show();
}
