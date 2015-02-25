#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    connect(&stuw, SIGNAL(modifyStu()), &courw, SLOT(initDialog()));
    connect(&stuw, SIGNAL(modifyStu()), &scow, SLOT(initDialog()));
    connect(&subw, SIGNAL(modifySub()), &courw, SLOT(initDialog()));
    connect(&subw, SIGNAL(modifySub()), &scow, SLOT(initDialog()));
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
    //课表管理
    subw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //课程安排管理
    courw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //学生成绩管理
    scow.show();
}

void mainDialog::on_pushButton_5_clicked()
{
    //用户信息管理
    userw.show();
}
