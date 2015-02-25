#include <QApplication>
#include <stdlib.h>
#include <QDebug>
#include <QTime>
#include "tetrixwindow.h"
#include "tetrixboard.h"
#include "common.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));

    QApplication app(argc, argv);

    //打开数据库
    database db;
    if(db.opendb("tetrix.db"))
    {
        //创建数据库表
        db.createtable();
    }

    TetrixWindow window;
    window.show();

//    TetrixBoard board;
//    board.resize(380,620);
//    board.start();
//    board.show();

    //初始化随机数种子
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return app.exec();
}
