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
    if (tables.contains("cracker", Qt::CaseInsensitive)
            && tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("goods", Qt::CaseInsensitive)
            && tables.contains("users", Qt::CaseInsensitive)
            && tables.contains("stockslog", Qt::CaseInsensitive)
            && tables.contains("stocks", Qt::CaseInsensitive)
            && tables.contains("borrowlog", Qt::CaseInsensitive)
            && tables.contains("usergoods", Qt::CaseInsensitive)
            && tables.contains("usergoodstemp", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号, 用户名, 注册码, 日期, 天数)
        query.exec("CREATE TABLE cracker(cname VARCHAR, cpwd VARCHAR, cdate VARCHAR, cnum INT)");
        //创建人员表(编号, 密码)
        query.exec("CREATE TABLE person(pwd VARCHAR)");
        //创建物品表(编号, 名称)
        query.exec("CREATE TABLE goods(goodsid INT PRIMARY KEY, gname VARCHAR)");
        //创建员工表(编号, 姓名, 身份证, 权限, 指纹)
        query.exec("CREATE TABLE users(usersid INT PRIMARY KEY, username VARCHAR, idcard VARCHAR, role INT, userzw VARCHAR)");
        //创建库存记录表(编号, 物品编号, 物品个数, 日期, 采购, 保管, 主管)
        query.exec("CREATE TABLE stockslog(stockslogid INT PRIMARY KEY, goodsid INT, num INT, createdate VARCHAR, buyerid INT, keeperid INT, leaderid INT)");
        //创建库存表(编号, 物品编号, 物品总数, 借出总数)
        query.exec("CREATE TABLE stocks(stocksid INT PRIMARY KEY, goodsid INT, num INT, borrownum INT)");
        //创建领取记录表(编号, 物品编号, 物品个数, 日期, 保管, 领取人, 借还标志)
        query.exec("CREATE TABLE borrowlog(borrowlogid INT PRIMARY KEY, goodsid INT, num INT, createdate VARCHAR, keeperid INT, userid INT, borrowflag INT)");
        //创建领取人员表(编号, 物品编号, 物品个数, 领取人)
        query.exec("CREATE TABLE usergoods(usergoodsid INT PRIMARY KEY, goodsid INT, num INT, userid INT)");
        //创建领取人员物品临时表(编号, 物品编号, 物品名称)
        query.exec("CREATE TABLE usergoodstemp(usergoodstempid INT PRIMARY KEY, goodsid INT, gname VARCHAR)");

        //插入注册信息
        query.exec("INSERT INTO cracker VALUES('zhiwen', '', '" + QDate::currentDate().toString("yyyy.MM.dd") + "', 60)");
        query.exec("INSERT INTO person VALUES('qwer')");
    }
}

void database::closedb()
{
    db.close();
}
