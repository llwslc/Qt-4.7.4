#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>

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

#endif // MYDATABASE_H
