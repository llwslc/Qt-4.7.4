#include <QtGui/QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //判断是否存在备份数据库
    if(QFile::exists("backup.db"))
    {
        //存在
        copyFileToPath("backup.db", "daysMatter.db", true);
        QFile::remove("backup.db");
    }

    //打开数据库
    if(db.opendb("daysMatter.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("dataBackup");    //数据备份

    loginWindow w;
    w.show();

    return a.exec();
}
