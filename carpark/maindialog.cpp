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
    painter.drawPixmap(0, 0, QPixmap(":/png/main.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void mainDialog::on_pushButton_clicked()
{
    //车位管理
    spacew.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //车辆出入库
    carw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //收益查询
    incomew.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //人员管理
    userw.show();
}
