#include <QtGui/QApplication>
#include "myfunc.h"
#include "wardrobewindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("wardrobe.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("clothes"); //衣服
    createFolder("matchclothes"); //衣服

    wardrobeWindow w;
    w.show();

    return a.exec();
}
