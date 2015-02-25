#include "userinfodialog.h"
#include "ui_userinfodialog.h"

userinfoDialog::userinfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userinfoDialog)
{
    ui->setupUi(this);
}

userinfoDialog::~userinfoDialog()
{
    delete ui;
}

void userinfoDialog::showEvent(QShowEvent *)
{
    QSqlQuery query;
    query.exec("select * from ownerinfo where name = '" + username + "'");
    qDebug() << "select * from ownerinfo where name = '" + username + "'" << endl;
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->lineEdit_5->setText(query.value(5).toString());
        ui->lineEdit_6->setText(query.value(6).toString());
        ui->lineEdit_7->setText(query.value(7).toString());
    }
}

void userinfoDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/3.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
