#include "admindialog.h"
#include "ui_admindialog.h"

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);

    connect(&adBookw, SIGNAL(addBook()), &adBorroww, SLOT(updateComboBox()));
    connect(&adStuw, SIGNAL(addStu()), &adBorroww, SLOT(updateComboBox()));
    connect(&adBookw, SIGNAL(addBook()), &adOverw, SLOT(updateComboBox()));
    connect(&adStuw, SIGNAL(addStu()), &adOverw, SLOT(updateComboBox()));
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_pushButton_clicked()
{
    //图书管理
    adBookw.show();
}

void adminDialog::on_pushButton_2_clicked()
{
    //学生管理
    adStuw.show();
}

void adminDialog::on_pushButton_3_clicked()
{
    //借阅管理
    adBorroww.show();
}

void adminDialog::on_pushButton_4_clicked()
{
    //图书检索
    bookSearchw.show();
}

void adminDialog::on_pushButton_5_clicked()
{
    //过期管理
    adOverw.show();
}

void adminDialog::on_pushButton_6_clicked()
{
    //退出登录
    this->close();
    emit loginOut();
}
