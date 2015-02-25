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
    if(!targetDir.exists()){    // 如果目标目录不存在, 则进行创建
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    // 当为目录时, 递归的进行copy
            if(!copyDirectoryFiles(fileInfo.filePath(),
                                   targetDir.filePath(fileInfo.fileName()),
                                   coverFileIfExist))
                return false;
        }
        else{            // 当允许覆盖操作时, 将旧文件进行删除操作
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
    if (tables.contains("users", Qt::CaseInsensitive)
            && tables.contains("guests", Qt::CaseInsensitive)
            && tables.contains("rooms", Qt::CaseInsensitive)
            && tables.contains("orders", Qt::CaseInsensitive)
            && tables.contains("lightauto", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在,则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号, 姓名, 密码, 权限)
        query.exec("create table users(usersid int primary key, name varchar, passwd varchar, role int)");
        //创建客户信息表(编号, 姓名, 性别, 年龄, 身份证号, 手机号, 会员)
        query.exec("create table guests(guestsid int primary key, name varchar, sex int, age int, idcard varchar, phone varchar, member int)");
        //创建房间信息表(编号, 房间号, 房间类型, 房价, 会员价)
        query.exec("create table rooms(roomsid int primary key, number varchar, type int, price int, mprice varchar)");
        //创建房间预订表(编号, 客户姓名, 房间号, 预订时间, 退房时间)
        query.exec("create table orders(ordersid int primary key, name varchar, number varchar, pre datetime, next datetime)");
        //创建灯泡自动表(编号, 灯编号, 开始时间, 结束时间, 是否自动)
        query.exec("create table lightauto(lightautoid int primary key, lightid int, pre varchar, next varchar, autoflag int)");

        //插入管理员初始用户名和密码
        query.exec("insert into users values(1, 'ad', '', 0)");
        query.exec("insert into users values(2, 'us', '', 1)");

        //插入灯泡自动表
        query.exec("insert into lightauto values(1, 1, '20:00:00', '23:30:00', 0)");
        query.exec("insert into lightauto values(2, 2, '20:00:00', '23:30:00', 0)");
        query.exec("insert into lightauto values(3, 3, '20:00:00', '23:30:00', 0)");
    }
}

void database::closedb()
{
    db.close();
}


QString loginName;

