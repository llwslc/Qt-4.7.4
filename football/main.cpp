#include <QtGui/QApplication>
#include "logindialog.h"
#include "mysqldata.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication::setStyle(new QPlastiqueStyle);

    QApplication a(argc, argv);

    //打开数据库
    mysqldata db;
    if(db.opendb("football.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("player");       //食物

    loginDialog w;
    w.show();

    return a.exec();
}
