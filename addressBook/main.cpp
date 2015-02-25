#include <QtGui/QApplication>
#include "common.h"
#include "maindialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("address.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("user");       //人物

    mainDialog w;
    w.show();

    return a.exec();
}
