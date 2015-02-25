#include <QtGui/QApplication>
#include "dialog.h"
#include "database.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QString sPath = a.applicationDirPath();
    a.addLibraryPath(sPath);

    QLibrary codecLib(sPath + "/codecs/qcncodecs4.dll");

    if (codecLib.load())
    {
    }
    else
    {
    }

    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    //打开数据库
    database db;
    if(db.opendb("database.db"))
    {
        //创建数据库表
        db.createtable();
    }

    Dialog w;
    w.show();

    return a.exec();
}
