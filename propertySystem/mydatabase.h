#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

class myDatabase
{
public:
    myDatabase();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;
};

//ÓÃ»§Ãû
extern QString username;

#endif // MYDATABASE_H
