#include "searchdialog.h"
#include "ui_searchdialog.h"

searchDialog::searchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchDialog)
{
    ui->setupUi(this);
}

searchDialog::~searchDialog()
{
    delete ui;
}

void searchDialog::on_pushButton_clicked()
{
    //预订房查询
    bookw.show();
}

void searchDialog::on_pushButton_2_clicked()
{
    //入住房查询
    inw.show();
}

void searchDialog::on_pushButton_3_clicked()
{
    //宿费提醒
    callw.show();
}
