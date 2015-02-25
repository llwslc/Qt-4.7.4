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
            && tables.contains("park", Qt::CaseInsensitive)
            && tables.contains("comego", Qt::CaseInsensitive)
            && tables.contains("parkstatus", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,密码)
        query.exec("create table person(personid int primary key, name varchar, passwd varchar)");
        //创建车位表(编号,状态)
        query.exec("create table park(parkid int primary key, status int)");
        //创建出入表(编号,车牌号,车位,入库时间,出库时间,费用)
        query.exec("create table comego(comegoid int primary key, plate varchar, park int, comedate datetime, go datetime, price int)");
        //创建状态表(编号,状态) 状态: 未使用 使用
        query.exec("create table parkstatus(parkstatusid int primary key, status varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'ad','')");
        //插入状态
        query.exec("insert into parkstatus values(0, '未使用')");
        query.exec("insert into parkstatus values(1, '使用')");
        query.exec("insert into parkstatus values(2, '预订')");
    }
}

void mydatabase::closedb()
{
    db.close();
}
