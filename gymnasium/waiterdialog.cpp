#include "waiterdialog.h"
#include "ui_waiterdialog.h"

waiterDialog::waiterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waiterDialog)
{
    ui->setupUi(this);

    connect(&memw, SIGNAL(addMoney()), &cashw, SLOT(updateTableModel()));
}

waiterDialog::~waiterDialog()
{
    delete ui;
}

void waiterDialog::on_pushButton_clicked()
{
    //会员管理
    memw.show();
}

void waiterDialog::on_pushButton_4_clicked()
{
    //收银管理
    cashw.show();
}

void waiterDialog::on_pushButton_5_clicked()
{
    //打卡下机
    QString sql;
    QSqlQuery query;

    sql = "update punch set outtime = '" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss") + "' where logtime = '"+ logtime +"'";
    query.exec(sql);

    QMessageBox::information(this,tr("punch"),tr("user punch out success!"),QMessageBox::Yes);

}

void waiterDialog::on_pushButton_6_clicked()
{
    //场地管理
    spacew.show();
}

void waiterDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/1.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
