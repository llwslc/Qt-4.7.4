#include "mydatabase.h"

mydatabase::mydatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool mydatabase::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void mydatabase::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("person", Qt::CaseInsensitive)
        && tables.contains("desk", Qt::CaseInsensitive)
        && tables.contains("dish", Qt::CaseInsensitive)
        && tables.contains("orderform", Qt::CaseInsensitive)
       )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号，姓名，密码，角色)   角色：0为管理员，1为服务员
        query.exec("create table person(personid int primary key, pname varchar, passwd varchar, role int)");
        //创建餐桌表(编号，桌状态)    状态：0空闲，1预定，2使用中
        query.exec("create table desk(deskid int primary key, status int)");
        //创建菜品表(编号，菜名，价格)
        query.exec("create table dish(dishid int primary key, dname varchar, dprice int)");
        //创建订单表(编号，日期，时间，桌号，金额，)
        query.exec("create table orderform(orderid int primary key, date varchar, time varchar, deskno int, income int)");
        //创建点菜表(编号, 菜名, 桌号)
        query.exec("create table dishDesk(dishDeskId int primary key, deskno int, dname varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'admin','admin',0)");
        query.exec("insert into person values(2,'ad','',0)");
        query.exec("insert into person values(3,'sv','',1)");
    }
}

void mydatabase::closedb()
{
    db.close();
}

