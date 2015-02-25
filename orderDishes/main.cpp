#include <QtGui/QApplication>
#include "loginwindow.h"
#include "mydatabase.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication::setStyle(new QPlastiqueStyle);
    QApplication a(argc, argv);

    //打开数据库
    mydatabase db;
    if(db.opendb("ordersystem.db"))
    {
        //创建数据库表
        db.createtable();
    }

    loginWindow logWindow;

    logWindow.show();

    return a.exec();
}
