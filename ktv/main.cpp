#include <QtGui/QApplication>
#include "function.h"
#include "frontWidget.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    //打开数据库
    mydatabase db;
    if(db.opendb("ktv.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("songsLibrary"); //歌曲库

    QApplication a(argc, argv);

    frontWidget w;
    w.show();

    return a.exec();
}
