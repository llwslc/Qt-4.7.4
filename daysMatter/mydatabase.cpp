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
    if (tables.contains("user", Qt::CaseInsensitive)
            && tables.contains("note", Qt::CaseInsensitive)
            && tables.contains("day", Qt::CaseInsensitive)
            && tables.contains("orderoption", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建登录人信息(编号，姓名，密码)
        query.exec("create table user(userid int primary key, name varchar, passwd varchar)");
        //创建日期表(编号,标题,日期,分类,重复,备注)
        query.exec("create table note(noteid int primary key, title varchar, data varchar, sort int, ditto int, remark varchar)");
        //创建倒计时表(编号,标题,天数,分类)
        query.exec("create table day(dayid int primary key, title varchar, daynum int, sort int)");
        //创建选项表(编号,排序方式)
        query.exec("create table orderoption(orderoptionid int primary key, rule int)");

        //插入管理员初始用户名和密码
        query.exec("insert into user values(1,'ad','')");
        query.exec("insert into orderoption values(1,0)");
    }
}

void mydatabase::closedb()
{
    db.close();
}

