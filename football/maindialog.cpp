#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    connect(&playerw, SIGNAL(addPlayer()), &scorew, SLOT(initComboBox()));
    connect(&gamew, SIGNAL(addGame()), &scorew, SLOT(initComboBox()));
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
    //球员信息管理
    playerw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //球员成绩管理
    scorew.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //俱乐部收支管理
    accw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //赛程管理
    gamew.show();
}
