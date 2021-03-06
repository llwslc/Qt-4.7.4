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
            && tables.contains("books", Qt::CaseInsensitive)
            && tables.contains("borrow", Qt::CaseInsensitive)
            && tables.contains("message", Qt::CaseInsensitive)
            )
    {
        //如果上述表名已存在，则不需要再次创建
        //qDebug("table exsited\n");
    }
    else
    {
        QSqlQuery query;
        //创建登录人信息(编号,姓名,密码)
        query.exec("create table users(usersid int primary key, name varchar, passwd varchar, role int)");
        //创建学生信息表(编号,姓名,密码,借书证编号,联系方式,借书证状态,学生照片)
        query.exec("create table students(studentsid int primary key, name varchar, passwd varchar, stucode varchar, phone varchar, status int, pic varchar)");
        //创建图书表(编号,名称,图书编号,出版社,作者,类型,入库时间,当前状态)
        query.exec("create table books(booksid int primary key, name varchar, bookcode varchar, publish varchar, aurhor varchar, type varchar, storagedate varchar, status int)");
        //创建借阅表(编号,图书编号,学生编号,借阅日期,归还日期,实际归还日期)
        query.exec("create table borrow(borrowid int primary key, bookcode varchar, stucode varchar, borrowdate varchar, returndate varchar, realreturndate varchar)");
        //创建提醒表(编号,图书编号,学生编号,归还日期)
        query.exec("create table message(messageid int primary key, bookcode varchar, stucode varchar, returndate varchar)");

        //插入管理员初始用户名和密码
        query.exec("insert into users values(1,'ad','', 0)");
        query.exec("insert into users values(2,'us','', 1)");
    }
}

void mydatabase::closedb()
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

QString loginName;
