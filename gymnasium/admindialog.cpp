#include "admindialog.h"
#include "ui_admindialog.h"

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);

    connect(&assw, SIGNAL(addAssessor()), &memw, SLOT(initComboBox()));
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_pushButton_clicked()
{
    //人员管理
    userw.show();
}

void adminDialog::on_pushButton_4_clicked()
{
    //顾问管理
    assw.show();
}

void adminDialog::on_pushButton_3_clicked()
{
    //会员管理
    memw.show();
}

void adminDialog::on_pushButton_5_clicked()
{
    //打卡管理
    punw.show();
}

void adminDialog::on_pushButton_2_clicked()
{
    //收银管理
    turnw.show();
}

void adminDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/11.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
