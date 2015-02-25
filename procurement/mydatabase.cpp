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
        qDebug("db file open error!");
        return false;
    }
    return true;
}

void mydatabase::createtable()
{
    QStringList tables = db.tables();
    if (tables.contains("person", Qt::CaseInsensitive)
            &&tables.contains("place", Qt::CaseInsensitive)
            &&tables.contains("hotel", Qt::CaseInsensitive))
    {
        //如果上述表名已存在,则不需要再次创建
        qDebug("table exsited!");
    }
    else
    {
        QSqlQuery query;
#if 0
        采购订单（采购订单编号 订单制作日期 订单审核人 供应商编号）
        采购订单商品明细表（商品编号 采购订单编号 商品数量 商品单价）
        采购合同（采购合同号 合同制作日期 合同审核人 ）
        采购合同商品明细表（采购合同号 商品编号 商品数量 商品单价）
        商品信息（商品编号 商品名称 商品单价 商品规格）
        供应商信息（供应商编号 供应商名称 ）
        收货单（收货单编号 制单日期 制单审核人 收货明细）
        收货商品明细（收货单编号 商品编号 商品数量）
        采购付款单（付款单编号 制单日期 审核人  付款人 付款金额 银行账号）

#endif
        //创建人员表(编号,姓名,密码)
        query.exec("create table person(personid int primary key, name varchar, passwd varchar)");
        //创建客户表(编号,姓名,电话,地址,邮箱,备注)
        query.exec("create table client(clientid int primary key, name varchar, phone varchar, address varchar, email varchar, note varchar)");
        //创建订单表(编号,订单编号,订单审核人,供应商编号,商品编号,商品数量,商品单价,订单日期,订单状态)
        query.exec("create table orderform(orderformid int primary key, orderformcode varchar, name varchar, officecode varchar, goodscode varchar, goodsnum varchar, goodsprice varchar, orderdata varchar, status int)");
        //创建产品表(编号,产品名称,产品数量,产品编号,产品单价,供货商)
        query.exec("create table goods(goodsid int primary key, name varchar, goodsnum varchar, goodscode varchar, goodsprice varchar, goodssupplier varchar)");
        //插入管理员初始用户名和密码
        query.exec("insert into person values(1,'ad','')");

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

