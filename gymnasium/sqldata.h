#ifndef SQLDATA_H
#define SQLDATA_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

class sqldata
{
public:
    sqldata();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;
};

#endif // SQLDATA_H
