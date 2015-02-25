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

void mainDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/4.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void mainDialog::on_pushButton_clicked()
{
    //货物管理
    goodw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //订单管理
    ordersw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //车辆管理
    carw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //用户管理
    userw.show();
}
