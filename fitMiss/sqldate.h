#ifndef SQLDATE_H
#define SQLDATE_H

#include "func.h"

class sqlDate
{
public:
    sqlDate();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;

};

#endif // SQLDATE_H
