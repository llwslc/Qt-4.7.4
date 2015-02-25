#ifndef MYDATA_H
#define MYDATA_H

#include "func.h"

class myData
{
public:
    myData();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;
};

#endif // MYDATA_H
