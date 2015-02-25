#include <QtGui/QApplication>
#include "mainwindow.h"

//1.CEveluation类:启发式估价器,对给定的棋盘进行估值.
//2.CMoveGenerator类:走法产生器,对给定的棋盘局面搜索出所有可能的走法.
//3.CSearchEngine类:搜索引擎基类.

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);    

    //创建相应的文件夹
    createFolder("chessboard");    //棋盘

    mainWindow w;
    w.show();

    return a.exec();
}
