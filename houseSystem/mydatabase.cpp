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
            && tables.contains("houses", Qt::CaseInsensitive)
            && tables.contains("business", Qt::CaseInsensitive)
            && tables.contains("record", Qt::CaseInsensitive)
            && tables.contains("property", Qt::CaseInsensitive)
            && tables.contains("grade", Qt::CaseInsensitive)
            && tables.contains("message", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号，姓名，密码，角色)   角色：0为管理员，1为普通用户
        query.exec("create table person(personid int primary key, pname varchar, passwd varchar, role int)");
        //创建楼盘表(编号，名称，价格，图片路径，图片路径1，图片路径2，图片路径3，图片路径4)
        query.exec("create table houses(houseid int primary key, hname varchar, hprice int, hpic varchar, hpic_1 varchar, hpic_2 varchar, hpic_3 varchar, hpic_4 varchar)");
        //创建交易表(编号，楼盘名，成交人，价格)
        query.exec("create table business(businessid int primary key, hname varchar, bname varchar, bprice int)");
        //创建档案表(编号，日期，时间，楼盘名，状态，图片路径) 状态：0为变更、1为预告、2为异议、3为查封
        query.exec("create table record(recordid int primary key, date varchar, time varchar, hname varchar, status int, rpic varchar)");
        //创建产权表(编号, 楼盘, 产权人，图片路径)
        query.exec("create table property(propertyId int primary key, hname varchar, dname varchar, ppic varchar)");
        //创建登记表(编号, 楼盘, 产权人，图片路径)
        query.exec("create table grade(gradeId int primary key, hname varchar, dname varchar, gpic varchar)");
        //创建留言表(编号, 用户名，楼盘名，星级，评价)
        query.exec("create table message(messageId int primary key, mname varchar, mhouse varchar, level int, data varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'admin','admin',0)");
        query.exec("insert into person values(2,'ad','',0)");
        query.exec("insert into person values(3,'us','',1)");
    }
}

void mydatabase::closedb()
{
    db.close();
}
