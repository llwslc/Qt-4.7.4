#include <QtGui/QApplication>
#include "logondialog.h"
#include "common.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);
    //打开数据库
    database db;
    if(db.opendb("alarmClock.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("music"); //歌曲

    logonDialog w;
    w.show();

    return a.exec();
}
