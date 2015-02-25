#include "sqldata.h"

sqldata::sqldata()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool sqldata::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void sqldata::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("member", Qt::CaseInsensitive)
            && tables.contains("punch", Qt::CaseInsensitive)
            && tables.contains("assessor", Qt::CaseInsensitive)
            && tables.contains("turnover", Qt::CaseInsensitive)
            && tables.contains("park", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,密码,角色)   角色：0为店长,1为服务员
        query.exec("create table person(personid int primary key, name varchar, passwd varchar, role int)");
        //创建会员表(编号,会员人名,性别,年龄,教练名,会员消费额度)
        query.exec("create table member(memberid int primary key, name varchar, sex int, age int, assname varchar, integral int)");
        //创建打卡表(编号,收银员名,登录时间,打卡退出时间)
        query.exec("create table punch(punchid int primary key, name varchar, logtime varchar, outtime varchar)");
        //创建顾问表(编号,顾问名字,性别,年龄,擅长)
        query.exec("create table assessor(assessorid int primary key, name varchar, sex int, age int, note varchar)");
        //创建营业额表格(编号,时间,项目名称,金额)
        query.exec("create table turnover(turnoverid int primary key, consumetime datetime, name varchar, price int)");
        //创建场地表(编号,状态)
        query.exec("create table park(parkid int primary key, status int)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'admin','admin',0)");
        query.exec("insert into person values(2,'ad','',0)");
        query.exec("insert into person values(3,'wa','',1)");

        query.exec("insert into member values(0,'空闲','','','','')");

    }
}

void sqldata::closedb()
{
    db.close();
}
