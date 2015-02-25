#include <QtGui/QApplication>
#include "logindialog.h"
#include "sqldate.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication::setStyle(new QPlastiqueStyle);

    QApplication a(argc, argv);

    //打开数据库
    sqlDate db;
    if(db.opendb("fitMiss.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("food");       //食物
    createFolder("cookbook");   //食谱
    createFolder("sports");     //运动

    loginDialog w;
    w.show();

    return a.exec();
}
