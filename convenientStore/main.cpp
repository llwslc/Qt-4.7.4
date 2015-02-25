#include <QtGui/QApplication>
#include "common.h"
#include "storedialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));


    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //打开数据库
    database db;
    if(db.opendb("store.db"))
    {
        //创建数据库表
        db.createtable();
    }

    storeDialog w;
    w.show();

    return a.exec();
}
