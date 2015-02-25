#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

class mydatabase
{
public:
    mydatabase();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;
};


#endif // MYDATABASE_H
