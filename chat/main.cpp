#include <QtGui/QApplication>
#include "common.h"
#include "logondialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    QApplication a(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("chat.db"))
    {
        //创建数据库表
        db.createtable();
    }

    logonDialog w;
    w.show();

    return a.exec();
}
