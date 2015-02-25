#include <QtGui/QApplication>
#include <QFile>
#include <QTextStream>
#include <QtWebKit/QWebView>
#include <QMessageBox>
#include <qstring>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
