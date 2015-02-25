#include "mydata.h"

myData::myData()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool myData::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void myData::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("user", Qt::CaseInsensitive)
            && tables.contains("room", Qt::CaseInsensitive)
            && tables.contains("checkin", Qt::CaseInsensitive)
            && tables.contains("staff", Qt::CaseInsensitive)
            && tables.contains("member", Qt::CaseInsensitive)
            && tables.contains("roomstatus", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建登录表(编号,登录名,密码)
        query.exec("create table user(userid int primary key, name varchar, passwd varchar)");
        //创建房间表(房间号,状态,图片路径1,图片路径2,图片路径3)
        query.exec("create table room(roomid int primary key, status int, pic_1 varchar, pic_2 varchar, pic_3 varchar)");
        //创建入住表(编号,房间号,姓名,身份证号,入住时间,消费额)
        query.exec("create table checkin(checkinid int primary key, roomnum int, name varchar, idnum varchar, date datetime, price int)");
        //创建员工表(编号,姓名,身份证号,职位,入职时间,工资,图片)
        query.exec("create table staff(staffid int primary key, name varchar, idnum varchar, post varchar, date datetime, wage int, pic varchar)");
        //创建会员表(编号,姓名,身份证号,消费额,消费时间,房间号,图片)
        query.exec("create table member(memberid int primary key, name varchar, idnum varchar, price int, date datetime, roomnum int)");
        //创建状态表(编号,状态) 状态: 未使用 使用 预订
        query.exec("create table roomstatus(roomstatusid int primary key, status varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into user values(1,'ad','')");

        query.exec("insert into roomStatus values(0, '未使用')");
        query.exec("insert into roomStatus values(1, '使用')");
        query.exec("insert into roomStatus values(2, '预订')");
    }
}

void myData::closedb()
{
    db.close();
}
