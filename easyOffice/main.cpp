#include <QtGui/QApplication>
#include "myfunc.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("easyOffice.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("supplies"); //办公用品

    loginDialog w;
    w.show();

    return a.exec();
}
