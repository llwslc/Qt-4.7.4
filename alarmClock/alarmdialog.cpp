#include "alarmdialog.h"
#include "ui_alarmdialog.h"

alarmDialog::alarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alarmDialog)
{
    ui->setupUi(this);
}

alarmDialog::~alarmDialog()
{
    delete ui;
}

void alarmDialog::on_timeEdit_timeChanged(const QTime &date)
{
    //1-2
    int idNum = 0;
    QString courseIdStr = QString("1");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox->checkState(), 10)
               + "')");
}

void alarmDialog::on_timeEdit_2_timeChanged(const QTime &date)
{
    //3-4
    int idNum = 0;
    QString courseIdStr = QString("2");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_2->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_2->checkState(), 10)
               + "')");
}

void alarmDialog::on_timeEdit_3_timeChanged(const QTime &date)
{
    //5-6
    int idNum = 0;
    QString courseIdStr = QString("3");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_3->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_3->checkState(), 10)
               + "')");
}

void alarmDialog::on_timeEdit_4_timeChanged(const QTime &date)
{
    //7-8
    int idNum = 0;
    QString courseIdStr = QString("4");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_4->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_4->checkState(), 10)
               + "')");
}

void alarmDialog::on_timeEdit_5_timeChanged(const QTime &date)
{
    //晚自习
    int idNum = 0;
    QString courseIdStr = QString("5");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_5->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_5->checkState(), 10)
               + "')");
}

void alarmDialog::on_checkBox_clicked()
{
    //1-2
    int idNum = 0;
    QString courseIdStr = QString("1");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox->checkState(), 10)
               + "')");
}

void alarmDialog::on_checkBox_2_clicked()
{
    //3-4
    int idNum = 0;
    QString courseIdStr = QString("2");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_2->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_2->checkState(), 10)
               + "')");
}

void alarmDialog::on_checkBox_3_clicked()
{
    //5-6
    int idNum = 0;
    QString courseIdStr = QString("3");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_3->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_3->checkState(), 10)
               + "')");
}

void alarmDialog::on_checkBox_4_clicked()
{
    //7-8
    int idNum = 0;
    QString courseIdStr = QString("4");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_4->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_4->checkState(), 10)
               + "')");
}

void alarmDialog::on_checkBox_5_clicked()
{
    //晚自习
    int idNum = 0;
    QString courseIdStr = QString("5");
    QSqlQuery query;
    query.exec("delete from alarmtime where userid = " + userid + " and courseid = " + courseIdStr);

    query.exec("select alarmtimeid from alarmtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into alarmtime values ('" + QString::number(idNum, 10) //插入数据库
               + "', '" + userid
               + "', '" + courseIdStr
               + "', '" + ui->timeEdit_5->time().toString("hh:mm:ss")
               + "', '" + QString::number(ui->checkBox_5->checkState(), 10)
               + "')");
}
