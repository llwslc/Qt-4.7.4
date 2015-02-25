#include <QtGui/QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
