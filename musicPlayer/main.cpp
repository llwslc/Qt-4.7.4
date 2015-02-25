#include <QApplication>
#include <QTextCodec>
#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    database db;
    if(db.opendb("music.db"))
    {
        //创建数据库
        db.createtable();
    }

    MyWidget w;
    w.show();
    
    return a.exec();
}
