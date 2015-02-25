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
            && tables.contains("classLevel", Qt::CaseInsensitive)
            && tables.contains("classType", Qt::CaseInsensitive)
            && tables.contains("classCon", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QString sql;
        QSqlQuery query;
        //创建登录表(编号, 名称, 密码)
        sql = "CREATE TABLE person(personid INT PRIMARY KEY, name VARCHAR, passwd VARCHAR)";
        query.exec(sql);
        //创建登录表(编号, 层次)
        sql = "CREATE TABLE classLevel(classLevelId INT PRIMARY KEY, name VARCHAR)";
        query.exec(sql);
        //创建登录表(编号, 类别)
        sql = "CREATE TABLE classType(classTypeId INT PRIMARY KEY, name VARCHAR)";
        query.exec(sql);
        //创建登录表(编号, 层次, 类别, 性质, 代码, 名称, 学时, 学分, 实验, 学期, 考核方式)
        sql = "CREATE TABLE classCon(classConId INT PRIMARY KEY, "
                + QString("cLevel INT, ")
                + QString("cType INT, ")
                + QString("cNature INT, ")
                + QString("cCode VARCHAR, ")
                + QString("cName VARCHAR, ")
                + QString("cHrs VARCHAR, ")
                + QString("cCrs VARCHAR, ")
                + QString("cTest VARCHAR, ")
                + QString("cTime INT, ")
                + QString("cExam INT ")
                + QString(")");
        query.exec(sql);

        //插入登录信息
        query.exec("INSERT INTO person VALUES(1, 'ad', 'ad')");
    }
}

void database::closedb()
{
    db.close();
}
