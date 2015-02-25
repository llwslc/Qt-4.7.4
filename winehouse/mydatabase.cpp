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
    if (tables.contains("room", Qt::CaseInsensitive)
            && tables.contains("checkin", Qt::CaseInsensitive)
            && tables.contains("roomstatus", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建房间表(房间号,状态)
        query.exec("create table room(roomid int primary key, status int)");
        //创建入住表(编号,房间号,姓名,身份证号,退房时间,消费额)
        query.exec("create table checkin(checkinid int primary key, roomnum int, name varchar, idnum varchar, date datetime, price int)");
        //创建状态表(编号,状态) 状态: 未使用 使用 预订
        query.exec("create table roomstatus(roomstatusid int primary key, status varchar)");

        query.exec("insert into roomstatus values(0, '未使用')");
        query.exec("insert into roomstatus values(1, '使用')");
        query.exec("insert into roomstatus values(2, '预订')");
    }
}

void mydatabase::closedb()
{
    db.close();
}
