#include "sqldate.h"

sqlDate::sqlDate()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool sqlDate::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void sqlDate::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("user", Qt::CaseInsensitive)
            && tables.contains("food", Qt::CaseInsensitive)
            && tables.contains("cookbook", Qt::CaseInsensitive)
            && tables.contains("sports", Qt::CaseInsensitive)
            && tables.contains("calrecord", Qt::CaseInsensitive)
            && tables.contains("weightrecord", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建登录人信息(编号，姓名，密码)
        query.exec("create table user(userid int primary key, passwd varchar)");
        //创建食物表(编号,名称,热量,指数,分类,图片)
        query.exec("create table food(foodid int primary key, name varchar, calories int, indexNum int, category varchar, pic varchar)");
        //创建食谱表(编号,名称,热量,指数,分类,图片)
        query.exec("create table cookbook(cookbookid int primary key, name varchar, calories int, indexNum int, category varchar, pic varchar)");
        //创建运动表(编号,名称,热量,指数,分类,图片)
        query.exec("create table sports(sportsid int primary key, name varchar, calories int, indexNum int, category varchar, pic varchar)");
        //创建热量记录表(编号,名称,热量,变量,分类,日期)
        query.exec("create table calrecord(calrecordid int primary key, name varchar, calories int, calvariable int, category int, date varchar)");
        //创建体重记录表(编号,体重,日期)
        query.exec("create table weightrecord(weightrecordid int primary key, weight int, date varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into user values(1,'ad')");
    }
}

void sqlDate::closedb()
{
    db.close();
}

