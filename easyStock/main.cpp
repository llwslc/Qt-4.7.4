#include <QtGui/QApplication>
#include "logindialog.h"
#include "mydatabase.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    QApplication a(argc, argv);

    //打开数据库
    mydatabase db;
    if(db.opendb("express.db"))
    {
        //创建数据库表
        db.createtable();
    }

    loginDialog w;
    w.show();

    return a.exec();
}
