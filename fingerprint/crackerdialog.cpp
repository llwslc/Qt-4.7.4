#include "crackerdialog.h"
#include "ui_crackerdialog.h"

crackerDialog::crackerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::crackerDialog)
{
    ui->setupUi(this);
}

crackerDialog::~crackerDialog()
{
    delete ui;
}

void crackerDialog::showEvent(QShowEvent *)
{
    init();
}

void crackerDialog::paintEvent(QPaintEvent *)
{}

void crackerDialog::closeEvent(QCloseEvent *)
{
}

void crackerDialog::init()
{
    QSqlQuery query;
    QString sql;
    QString cname = "";
    QString cpwd = "";
    QString cdate = "";
    int dayNum = 0;
    int cnum = 0;

    sql = "select cname, cpwd, cdate, cnum from cracker";
    query.exec(sql);
    while(query.next())
    {
        cname = query.value(0).toString();
        cpwd = query.value(1).toString();
        cdate = query.value(2).toString();
        cnum = query.value(3).toInt();
    }

    if(cpwd == Encrypt(cname))
    {
        ui->label->setText("注册信息如下:");
    }
    else
    {
        sql = "update cracker set cpwd = '' where cname = '" + cname + "'";
        cpwd = "";
        query.exec(sql);

        dayNum = QDate::fromString(cdate, "yyyy.MM.dd").daysTo(QDate::currentDate());
        dayNum = ((cnum - dayNum) > 0) ? (cnum - dayNum) : 0;
        ui->label->setText("试用日期还剩 " + QString::number(dayNum) + " 天");
    }
    ui->lineEdit->setText(cname);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setText(cpwd);

    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    //c8e71556394336cecf081b79b84294c4297dbae8
}

void crackerDialog::on_pushButton_clicked()
{
    //注册
    QString strName = ui->lineEdit->text().trimmed();
    QString strPwd = ui->lineEdit_2->text().trimmed();
    if(strPwd == Encrypt(strName))
    {
        //注册成功
        QSqlQuery query;
        QString sql;
        sql = "update cracker set cpwd = '" + strPwd
                + "' where cname = '" + strName + "'";
        query.exec(sql);
        QMessageBox::information(NULL, "success.", "注册成功!");
    }
    else
    {
        //注册失败
        QMessageBox::information(NULL, "error.", "注册失败!");
    }
}

void crackerDialog::on_pushButton_3_clicked()
{
    //修改密码
    QSqlQuery query;
    QString sql;

    QString oldPwd = ui->lineEdit_3->text().trimmed();
    QString newPwd1 = ui->lineEdit_4->text().trimmed();
    QString newPwd2 = ui->lineEdit_5->text().trimmed();

    if(ui->lineEdit_4->text().right(1) == " ")
    {
        QMessageBox::information(NULL, "error.", "密码不能以空格结尾!");
        return;
    }

    if(ui->lineEdit_5->text().right(1) == " ")
    {
        QMessageBox::information(NULL, "error.", "密码不能以空格结尾!");
        return;
    }

    sql = "select * from person where pwd = '" + oldPwd + "'";
    query.exec(sql);

    if (query.next())
    {
        if(newPwd1 == newPwd2)
        {
            sql = "update person set pwd = '" + newPwd1 + "' where pwd = '" + oldPwd + "'";
            query.exec(sql);

            ui->lineEdit_3->clear();
            ui->lineEdit_4->clear();
            ui->lineEdit_5->clear();
            QMessageBox::information(NULL, "success.", "修改成功!");
        }
        else
        {
            QMessageBox::information(NULL, "error.", "两次输入的新密码输入不一致!");
        }
    }
    else
    {
        QMessageBox::information(NULL, "error.", "密码错误!");
    }
}

void crackerDialog::on_pushButton_2_clicked()
{
    //取消
    this->close();
}

