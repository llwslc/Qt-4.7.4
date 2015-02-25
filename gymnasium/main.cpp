#include <QtGui/QApplication>
#include "logindialog.h"
#include "sqldata.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    sqldata db;
    if(db.opendb("gymnasium.db"))
    {
        //创建数据库表
        db.createtable();
    }

    loginDialog w;
    w.show();

    return a.exec();
}
