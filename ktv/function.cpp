#include "function.h"

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
    if (tables.contains("person", Qt::CaseInsensitive)
            && tables.contains("member", Qt::CaseInsensitive)
            && tables.contains("songsLibrary", Qt::CaseInsensitive)
            && tables.contains("songsList", Qt::CaseInsensitive)
            && tables.contains("roomNum", Qt::CaseInsensitive)
            && tables.contains("roomStatus", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建人员表(编号,姓名,密码,角色)   角色：0为管理员,1为服务员
        query.exec("create table person(personid int primary key, name varchar, passwd varchar, role int)");
        //创建会员表(编号,会员人,会员消费额度,图片路径)
        query.exec("create table member(memberid int primary key, name varchar, amount varchar)");
        //创建歌曲库表(编号,歌曲名,演唱者,被点次数,歌曲路径)
        query.exec("create table songsLibrary(songsLibraryid int primary key, name varchar, artist varchar, selected int, path varchar)");
        //创建点歌表(编号,歌曲名,演唱者,歌曲路径)
        query.exec("create table songsList(songsListid int primary key, name varchar, artist varchar, path varchar)");
        //创建房间表(编号,状态)
        query.exec("create table roomNum(roomNumid int primary key, status int)");
        //创建状态表(编号,状态) 状态: 未使用 使用 预订
        query.exec("create table roomStatus(roomStatusid int primary key, status varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'admin','admin',0)");
        query.exec("insert into person values(2,'ad','',0)");
        query.exec("insert into person values(3,'sv','',1)");

        query.exec("insert into roomStatus values(0, '未使用')");
        query.exec("insert into roomStatus values(1, '使用')");
        query.exec("insert into roomStatus values(2, '预订')");
    }
}

void mydatabase::closedb()
{
    db.close();
}

