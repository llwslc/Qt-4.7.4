#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QtGui>
#include <QtCore>
#include <QtDebug>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QtNetwork>
#include <QHash>
#include <QtSql>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QWebView>
#include <QFile>
#include <QWebFrame>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QEvent>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

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

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
//创建文件夹
bool createFolder(const QString dir);

#endif // MYDATABASE_H
