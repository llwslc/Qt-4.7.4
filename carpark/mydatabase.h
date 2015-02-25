#ifndef MYDATABASE_H
#define MYDATABASE_H

#include "common.h"

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
