#include <QtGui/QApplication>
#include "func.h"
#include "mydata.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    myData db;
    if(db.opendb("hotel.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("room"); //房间
    createFolder("staff"); //员工

    loginDialog w;
    w.show();

    return a.exec();
}

