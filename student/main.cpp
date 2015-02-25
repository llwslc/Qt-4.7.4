#include <QtGui/QApplication>
#include "logindialog.h"
#include "mydatabase.h"

//创建文件夹
bool createFolder(const QString dir)
{
    QDir *temp = new QDir;
    bool exist = temp->exists(dir);
    if(exist)
        return false;
    else
    {
        bool ok = temp->mkdir(dir);
        if(ok)
            qDebug() << "success" << endl;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //打开数据库
    mydatabase db;
    if(db.opendb("student.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("student");    //数据备份

    loginDialog w;
    w.show();

    return a.exec();
}
