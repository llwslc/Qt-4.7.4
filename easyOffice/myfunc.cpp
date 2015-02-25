#include "myfunc.h"

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\", "/");
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

//数据库
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
    if (tables.contains("users", Qt::CaseInsensitive)
            && tables.contains("clothes", Qt::CaseInsensitive)
            && tables.contains("matchclothes", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在, 则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建登录人信息(编号, 姓名, 密码, 权限)
        query.exec("create table users(usersid int primary key, name varchar, passwd varchar, role int)");
        //创建衣物表(编号, 名称, 类型, 季节, 分类, 品牌, 价格, 时间, 存放地, 购买地, 备注, 图片路径)
        query.exec("create table clothes(clothesid int primary key, name varchar, type int, season int, classtype int, brand varchar, price int, time varchar, storeplace varchar, buyplace varchar, note varchar, pic varchar)");
        //创建搭配表(编号, 名称, 类型, 季节, 分类, 日期, 图片路径)
        query.exec("create table matchclothes(matchclothesid int primary key, name varchar, type int, season int, classtype int, data varchar, pic varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into users values(1, 'ad', '', 0)");
        query.exec("insert into users values(2, 'us', '', 1)");
    }
}

void database::closedb()
{
    db.close();
}

QString loginName;
