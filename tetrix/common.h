#ifndef COMMON_H
#define COMMON_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QtNetwork>
#include <QListWidgetItem>

//Êý¾Ý¿â
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

#endif // COMMON_H
