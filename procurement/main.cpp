#include <QtGui/QApplication>
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication::setStyle(new QPlastiqueStyle);

    QApplication a(argc, argv);

    //打开数据库
    mydatabase db;
    if(db.opendb("procurement.db"))
    {
        //创建数据库表
        db.createtable();
    }

    loginDialog w;
    w.show();

    return a.exec();
}
