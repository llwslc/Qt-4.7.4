#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include <QtNetwork/QNetworkConfigurationManager>
#include <QtNetwork/QNetworkSession>

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

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
//创建文件夹
bool createFolder(const QString dir);

#endif // DATABASE_H
