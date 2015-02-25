#ifndef MYDATABASE_H
#define MYDATABASE_H

#include "common.h"

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
