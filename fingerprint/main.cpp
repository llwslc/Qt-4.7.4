#include <QtGui/QApplication>
#include "common.h"
#include "database.h"
#include "logondialog.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    //打开数据库
    database db;
    if(db.opendb("fingerprint.db"))
    {
        //创建数据库表
        db.createtable();
    }

    logonDialog w;
    w.show();

    return a.exec();
}
