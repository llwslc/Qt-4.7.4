#include <QtGui/QApplication>
#include "maindialog.h"
#include "myfunc.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    //打开数据库
    mydatabase db;
    if(db.opendb("sleepmusic.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("music"); //歌曲
    createFolder("pic"); //图片

    QApplication a(argc, argv);
    mainDialog w;
    w.show();

    return a.exec();
}
