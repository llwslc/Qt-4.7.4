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
    if (tables.contains("users", Qt::CaseInsensitive)
            && tables.contains("students", Qt::CaseInsensitive)
            && tables.contains("subjucts", Qt::CaseInsensitive)
            && tables.contains("courses", Qt::CaseInsensitive)
            && tables.contains("scores", Qt::CaseInsensitive)
            && tables.contains("note", Qt::CaseInsensitive)
            && tables.contains("day", Qt::CaseInsensitive)
            && tables.contains("orderoption", Qt::CaseInsensitive)
            && tables.contains("mycourse", Qt::CaseInsensitive)
            && tables.contains("mynote", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建登录人信息(编号, 姓名, 密码)
        query.exec("create table users(usersid int primary key, name varchar, passwd varchar)");
        //创建学生信息表(编号, 姓名, 身份证, 专业, 班级, 学号, 照片)
        query.exec("create table students(studentsid int primary key, name varchar, idcard varchar, spec varchar, classid varchar, schid varchar, pic varchar)");
        //创建课程表(编号, 科目)
        query.exec("create table subjucts(subjuctsid int primary key, name varchar)");
        //创建上课表(编号, 科目, 班级, 星期, 时间)
        query.exec("create table courses(coursesid int primary key, subjucts varchar, classid varchar, weekday varchar, time varchar)");
        //创建成绩表(编号, 科目, 学号, 成绩)
        query.exec("create table scores(scoresid int primary key, subjucts varchar, schid varchar, score int)");
        //创建我的课程表(编号, 班级id, 课程, 行, 列)
        query.exec("create table mycourse(mycourseid int primary key, classid varchar, name varchar, colindex int, rowindex int)");
        //创建我的课程备注表(编号, 用户id, 备注, 行, 列)
        query.exec("create table mynote(mynoteid int primary key, userid varchar, note varchar, colindex int, rowindex int)");

        //创建日期表(编号, 标题, 日期, 分类, 重复, 备注)
        query.exec("create table note(noteid int primary key, title varchar, data varchar, sort int, ditto int, remark varchar)");
        //创建倒计时表(编号, 标题, 天数, 分类)
        query.exec("create table day(dayid int primary key, title varchar, daynum int, sort int)");
        //创建选项表(编号, 排序方式)
        query.exec("create table orderoption(orderoptionid int primary key, rule int)");

        //插入管理员初始用户名和密码
        query.exec("insert into users values(1, 'ad', '')");
        query.exec("insert into orderoption values(1, 0)");
    }
}

void mydatabase::closedb()
{
    db.close();
}
