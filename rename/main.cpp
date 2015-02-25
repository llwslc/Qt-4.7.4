#include <QtGui/QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
