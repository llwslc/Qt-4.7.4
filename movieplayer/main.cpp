#include <QtGui>
#include "common.h"
#include "logondialog.h"

int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    //打开数据库
    database db;
    if(db.opendb("movie.db"))
    {
        //创建数据库表
        db.createtable();
    }

    //    MovieForm *movieForm=new MovieForm;
    //    movieForm->show();

    logonDialog w;
    w.show();

    return app.exec();
}
