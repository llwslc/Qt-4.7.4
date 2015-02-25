#include "mydatabase.h"

myDatabase::myDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool myDatabase::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void myDatabase::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("waterchanges", Qt::CaseInsensitive)
            && tables.contains("electricitychanges", Qt::CaseInsensitive)
            && tables.contains("gaschanges", Qt::CaseInsensitive)
            && tables.contains("lights", Qt::CaseInsensitive)
            && tables.contains("boardcase", Qt::CaseInsensitive)
            && tables.contains("equipment", Qt::CaseInsensitive)
            && tables.contains("park", Qt::CaseInsensitive)
            && tables.contains("parkstatus", Qt::CaseInsensitive)
            && tables.contains("ownerinfo", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,密码,角色)   角色：0为管理员, 1为用户
        query.exec("create table person(personid int primary key, name varchar, passwd varchar, role int)");
        //创建水费表(编号,户主,日期,缴费,余额)
        query.exec("create table waterchanges(waterchangesid int primary key, name varchar, date datetime, payment int, balance int)");
        //创建电费表(编号,户主,日期,缴费,余额)
        query.exec("create table electricitychanges(electricitychangesid int primary key, name varchar, date datetime, payment int, balance int)");
        //创建煤气费表(编号,户主,日期,缴费,余额)
        query.exec("create table gaschanges(gaschangesid int primary key, name varchar, date datetime, payment int, balance int)");
        //创建路灯表(编号,设备名,状态,描述,日期)
        query.exec("create table lights(lightsid int primary key, name varchar, status int, detail varchar, date varchar)");
        //创建广播表(编号,设备名,状态,描述,日期)
        query.exec("create table boardcase(boardcaseid int primary key, name varchar, status int, detail varchar, date varchar)");
        //创建其他表(编号,设备名,状态,描述,日期)
        query.exec("create table equipment(equipmentid int primary key, name varchar, status int, detail varchar, date varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'admin','admin',0)");
        query.exec("insert into person values(2,'ad','',0)");
        query.exec("insert into person values(3,'us','',1)");

        //创建车位表(编号,状态)
        query.exec("create table park(parkid int primary key, status int)");
        //创建状态表(编号,状态) 状态: 未使用 使用
        query.exec("create table parkstatus(parkstatusid int primary key, status varchar)");
        //插入状态
        query.exec("insert into parkstatus values(0, '未使用')");
        query.exec("insert into parkstatus values(1, '使用')");
        query.exec("insert into parkstatus values(2, '预订')");

        //用户信息表
        query.exec("create table ownerinfo(ownerinfoid int primary key, name varchar, pwd varchar, loufang varchar, danyuan varchar, louceng varchar, fangjian varchar, dianhua varchar)");
        query.exec("insert into ownerinfo values(1,'us','','12','3','4','5','041184831234')");
    }
}

void myDatabase::closedb()
{
    db.close();
}

QString username;
