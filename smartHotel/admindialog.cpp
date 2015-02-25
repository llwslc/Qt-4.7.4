#include "admindialog.h"
#include "ui_admindialog.h"

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);

    connect(&guestw, SIGNAL(modGuest()), &orderw, SLOT(initGuest()));
    connect(&roomw, SIGNAL(modRoom()), &orderw, SLOT(initRoom()));
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_pushButton_clicked()
{
    //客户信息
    guestw.show();
}

void adminDialog::on_pushButton_2_clicked()
{
    //房间信息
    roomw.show();
}

void adminDialog::on_pushButton_3_clicked()
{
    //入住信息
    orderw.show();
}

void adminDialog::on_pushButton_4_clicked()
{
    //人员管理
    userw.show();
}
