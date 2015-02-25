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
    //房间预览
    roompreDlg.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //入住信息
    checkinDlg.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //员工管理
    staffDlg.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //会员管理
    memberDlg.show();
}

void mainDialog::on_pushButton_5_clicked()
{
    //账户管理
    accountDlg.show();
}
