#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    //中文支持
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    //固定写法
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
