#include "mysqldata.h"

mysqldata::mysqldata()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
}

bool mysqldata::opendb(QString dbname)
{
    db.setDatabaseName(dbname);
    if(!db.open())
    {
        qDebug("db file open error");
        return false;
    }
    return true;
}

void mysqldata::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("info", Qt::CaseInsensitive)
            && tables.contains("score", Qt::CaseInsensitive)
            && tables.contains("account", Qt::CaseInsensitive)
            && tables.contains("game", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,密码)
        query.exec("create table person(personid int primary key, name varchar, passwd varchar)");
        //创建球员信息表(编号,姓名,身份证,生日,住址,邮箱,电话,薪酬,照片)
        query.exec("create table info(infoid int primary key, name varchar, idcard varchar, birthday datetime, address varchar, email varchar, phonenum varchar, price int, pic varchar)");
        //创建球员成绩表(编号,姓名,赛事名称,进球时间)
        query.exec("create table score(scoreid int primary key, name varchar, game varchar, scoretime datetime)");
        //创建俱乐部收支表(编号,项目,收入,支出,日期)
        query.exec("create table account(accountid int primary key, name varchar, come int, go int, curdate datetime)");
        //创建赛事管理表(编号,项目,日期,地点,出场人数,预计支出)
        query.exec("create table game(gameid int primary key, name varchar, gamedate datetime, address varchar, personnum int, price int)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'ad','')");
    }
}

void mysqldata::closedb()
{
    db.close();
}

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
