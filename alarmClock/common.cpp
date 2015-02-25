#include "common.h"

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    // 如果目标目录不存在，则进行创建
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    // 当为目录时，递归的进行copy
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else{            // 当允许覆盖操作时，将旧文件进行删除操作
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            // 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                            targetDir.filePath(fileInfo.fileName()))){
                return false;
            }
        }
    }
    return true;
}

//创建文件夹
bool createFolder(const QString dir)
{
    QDir *temp = new QDir;
    bool exist = temp->exists(dir);
    if(exist)
        qDebug() << "文件夹已存在" << endl;
    else
    {
        bool ok = temp->mkdir(dir);
        if(ok)
            qDebug() << "文件夹创建成功" << endl;
    }

    return true;
}



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
    if (tables.contains("user", Qt::CaseInsensitive)
            && tables.contains("alarmtime", Qt::CaseInsensitive)
            && tables.contains("music", Qt::CaseInsensitive)
            && tables.contains("course", Qt::CaseInsensitive)
            && tables.contains("note", Qt::CaseInsensitive)
            && tables.contains("day", Qt::CaseInsensitive)
            && tables.contains("orderoption", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号, 姓名, 密码)
        query.exec("create table user(userid int primary key, name varchar, passwd varchar)");
        //创建音乐表(编号, 音乐名称, 路径, 是否铃声)
        query.exec("create table music(musicid int primary key, name varchar, path varchar, alarmsing int)");
        //创建课程表(编号, 用户id, 课程, 行, 列)
        query.exec("create table course(courseid int primary key, userid int, name varchar, colindex int, rowindex int)");
        //创建闹钟表(编号, 用户id, 课程id, 闹钟时间, 是否提醒)
        query.exec("create table alarmtime(alarmtimeid int primary key, userid int, courseid int, alarmclock datetime, alarmflag int)");


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

void database::closedb()
{
    db.close();
}

QString userid;

//计算日期差
int datedef(QString dateStr, int rule)
{
    int expireFlag = false; //是否过期

    int curYear = QDate::currentDate().toString("yyyy").toInt();
    int curMonth = QDate::currentDate().toString("MM").toInt();
    int curDay = QDate::currentDate().toString("dd").toInt();
    QString curWeek = QDate::currentDate().toString("ddd");
    int curWeekInt;

    QDate sqlDate = QDate::fromString(dateStr, "yyyy.MM.dd");
    int sqlYear = sqlDate.toString("yyyy").toInt();
    int sqlMonth = sqlDate.toString("MM").toInt();
    int sqlDay = sqlDate.toString("dd").toInt();
    QString sqlWeek = sqlDate.toString("ddd");
    int sqlWeekInt;

    int i;
    int day=0,dayt1=0,dayt2=0;
    int result;

    qDebug() << "curYear = " << curYear;
    qDebug() << "curMonth = " << curMonth;
    qDebug() << "curDay = " << curDay;
    qDebug() << "sqlYear = " << sqlYear;
    qDebug() << "sqlMonth = " << sqlMonth;
    qDebug() << "sqlDay = " << sqlDay;

    switch(rule)
    {
    case 0:
        //0 不重复
        if(curYear > sqlYear)
        {
            //不重复,如果年已经过期
            swapNum(&curYear, &sqlYear);
            swapNum(&curMonth, &sqlMonth);
            swapNum(&curDay, &sqlDay);

            expireFlag = true;
        }
        else
        {
            //年没有过期
            if(curMonth > sqlMonth)
            {
                //月份过期
                swapNum(&curMonth, &sqlMonth);
                swapNum(&curDay, &sqlDay);

                expireFlag = true;
            }
            else
            {
                //月份没有过期
                if(curDay > sqlDay)
                {
                    //日期过期
                    swapNum(&curDay, &sqlDay);

                    expireFlag = true;
                }
            }
        }
        break;
    case 1:
        //1 按周重复
        curWeekInt = weekToInt(curWeek);
        sqlWeekInt = weekToInt(sqlWeek);
        if (curWeekInt > sqlWeekInt)
        {
            //星期过期
            result = sqlWeekInt+7-curWeekInt;
        }
        else
        {
            result = sqlWeekInt - curWeekInt;
        }
        qDebug() << "curWeekInt = " << curWeekInt;
        qDebug() << "sqlWeekInt = " << sqlWeekInt;
        qDebug() << "result = " << result;
        break;
    case 2:
        //2 按月重复
        sqlYear = curYear;
        if(curMonth > sqlMonth)
        {
            //月份过期
            if(curDay > sqlDay)
            {
                //日期过期
                sqlMonth = curMonth+1;
            }
            else
            {
                //日期没有过期
                sqlMonth = curMonth;
            }
        }
        else
        {
            //月份没有过期
            if(curDay > sqlDay)
            {
                //日期过期
                sqlMonth = curMonth+1;
            }
            else
            {
                //日期没有过期
                sqlMonth = curMonth;
            }
        }
        break;
    case 3:
        //3 按年重复
        if(curYear > sqlYear)
        {
            //年已经过期
            sqlYear = curYear+1;
        }
        else
        {
            //年没有过期
            if(curMonth > sqlMonth)
            {
                //月份过期
                sqlYear = curYear+1;
            }
            else
            {
                if(curDay > sqlDay)
                {
                    //日期过期
                    sqlYear = curYear+1;
                }
                else
                {
                }
            }
        }
        break;
    default:
        break;
    }

    int d[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},{0,31,29,31,30,31,30,31,31,30,31,30,31}};
    for(i=curYear; i<sqlYear; i++)
        if(leap(i) == false)
            day += 365;
        else
            day += 366;

    for(i=1; i<curMonth; i++)
        dayt1 += d[leap(curYear)][i];
    dayt1 += curDay;

    for(i=1; i<sqlMonth; i++)
        dayt2 += d[leap(sqlYear)][i];
    dayt2 += sqlDay;


    if(rule == 1)
    {
        //星期
    }
    else
    {
        result = day+dayt2-dayt1;
        if(expireFlag == true)
        {
            //日期过期
            result = 0-result;
        }
    }
    return result;
}
//是否闰年
int leap(int year)
{
    if(year%400==0 ||(year%4==0&&year%100!=0))
        return true;
    else
        return false;
}

//交换两个数据
void swapNum(int *pre, int *next)
{
    int temp;
    temp = *pre;
    *pre = *next;
    *next = temp;
}

//星期转数字
int weekToInt(QString weekStr)
{
    if(weekStr == QString("周一"))
    {
        return 1;
    }
    else if(weekStr == QString("周二"))
    {
        return 2;
    }
    else if(weekStr == QString("周三"))
    {
        return 3;
    }
    else if(weekStr == QString("周四"))
    {
        return 4;
    }
    else if(weekStr == QString("周五"))
    {
        return 5;
    }
    else if(weekStr == QString("周六"))
    {
        return 6;
    }
    else if(weekStr == QString("周日"))
    {
        return 7;
    }else
    {
        return 0;
    }

}

int itemDelButtonFlag;
QPoint windowsPos;
QString viewTitle;
