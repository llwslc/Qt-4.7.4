#ifndef DATABASE_H
#define DATABASE_H

#include "function.h"

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

#endif // DATABASE_H
