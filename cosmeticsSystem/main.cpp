#include <QtGui/QApplication>
#include "loginsystem.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication::setStyle(new QCleanlooksStyle);
    QApplication a(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("cosmeticsSystem.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //创建相应的文件夹
    createFolder("goods"); //商品
    createFolder("depot"); //仓库
    createFolder("member");//会员

    loginSystem w;
    w.show();

    return a.exec();
}
