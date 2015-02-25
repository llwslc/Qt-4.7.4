#include "staffdialog.h"
#include "ui_staffdialog.h"

staffDialog::staffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staffDialog)
{
    ui->setupUi(this);
}

staffDialog::~staffDialog()
{
    delete ui;
}

void staffDialog::on_pushButton_clicked()
{
    //查询物品
    warw.show();
}

void staffDialog::on_pushButton_2_clicked()
{
    //修改密码
    pwdw.show();
}
