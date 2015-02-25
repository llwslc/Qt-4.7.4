#include <QtGui/QApplication>
#include "common.h"
#include "logondialog.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    QApplication a(argc, argv);

    //�����ݿ�
    database db;
    if(db.opendb("smart.db"))
    {
        //�������ݿ��
        db.createtable();
    }

    logonDialog w;
    w.show();
    //w.userw.show();

    return a.exec();
}