#include <QtGui/QApplication>
#include "logdialog.h"
#include"mydatabase.h"
#include<qtextcodec.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));
    //打开数据库
    mydatabase  db;
    if(db.opendb("ordersystem.db"))
    {
        //创建数据库表
        db.createtable();
    }


    logDialog w;
    w.show();

    //进入事件循环
    a.exec();

    //关闭数据库
    db.closedb();

    return 0;
}
