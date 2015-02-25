#ifndef MUFUNC_H
#define MUFUNC_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
//创建文件夹
bool createFolder(const QString dir);
//数据库
class database
{
public:
    database();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;
};

#endif // MUFUNC_H
