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
    if(db.opendb("houseSystem.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("house");    //楼盘
    createFolder("property"); //产权
    createFolder("grade");    //登记
    createFolder("record");   //档案

    loginWindow logWindow;

    logWindow.show();

    return a.exec();
}
