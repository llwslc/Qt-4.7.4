#include <QtGui/QApplication>
#include "common.h"
#include "database.h"
#include "logondialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("class.db"))
    {
        //创建数据库表
        db.createtable();
    }

    logonDialog w;
    w.show();

    return a.exec();
}
