#ifndef MYDATABASE_H
#define MYDATABASE_H
#include<QSqlDatabase>

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
