#include "database.h"

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool database::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void database::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("goods", Qt::CaseInsensitive)
            && tables.contains("depot", Qt::CaseInsensitive)
            && tables.contains("turnover", Qt::CaseInsensitive)
            && tables.contains("member", Qt::CaseInsensitive)
            && tables.contains("punch", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,密码,角色)   角色：0为店长,1为服务员, 2为仓库管理员
        query.exec("create table person(personid int primary key, pname varchar, passwd varchar, role int)");
        //创建商品表(编号,名称,价格,仓库剩余数量,图片路径)
        query.exec("create table goods(goodsid int primary key, gname varchar, gprice int, gnumber int, gpic varchar)");
        //创建仓库表(编号,名称,进价,仓库剩余数量,图片路径)
        query.exec("create table depot(depotid int primary key, dname varchar, dprice int, dnumber int, dpic varchar)");
        //创建营业额表格(编号,日期,时间,商品名,个数,金额)
        query.exec("create table turnover(turnoverid int primary key, turnoverdate datetime, time varchar, tname varchar, tnumber int, tprice int)");
        //创建会员表(编号, 会员人名, 会员消费额度, 图片路径)
        query.exec("create table member(memberid int primary key, mname varchar, mamount varchar, mpic varchar)");
        //创建打卡表(编号, 收银员名, 登录时间, 打卡退出时间)
        query.exec("create table punch(punchid int primary key, name varchar, logtime varchar, outtime varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'admin','admin',0)");
        query.exec("insert into person values(2,'ad','',0)");
        query.exec("insert into person values(3,'us','',1)");
        query.exec("insert into person values(4,'de','',2)");
    }
}

void database::closedb()
{
    db.close();
}
