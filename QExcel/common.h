#ifndef COMMON_H
#define COMMON_H

#include <QtCore>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QHash>
#include <QtSql>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QEvent>

#define TBOPENCOMCOL 0    //列表读取单位名称列号
#define TBOPENSALCOL 1    //列表读取当日产量列号
#define TBOPENPROCOL 2    //列表读取当日销量列号
#define TBOPENSTKCOL 3    //列表读取期末库存列号
#define TBOPENTRACOL 4    //列表读取铁路运输列号
#define TBOPENCARCOL 5    //列表读取汽车运输列号
#define TBOPENREMCOL 6    //列表读取销量备注列号

#define XLSOPENCOMROW 5   //文件读取行号
#define XLSOPENCOMCOL 2   //文件读取单位名称列号
#define XLSOPENSALCOL 3   //文件读取当日产量列号
#define XLSOPENPROCOL 5   //文件读取当日销量列号
#define XLSOPENSTKCOL 7   //文件读取期末库存列号
#define XLSOPENTRACOL 8   //文件读取铁路运输列号
#define XLSOPENCARCOL 9   //文件读取汽车运输列号
#define XLSOPENREMCOL 10  //文件读取销量备注列号

#define XLSSAVETIMROW 1   //文件保存时间行号
#define XLSSAVETIMCOL 1   //文件保存时间列号

#define XLSSAVECOMROW 5   //文件保存行号
#define XLSSAVEENDROW 15  //文件保存结束行号
#define XLSSAVECOMCOL 2   //文件保存单位名称列号
#define XLSSAVESALCOL 3   //文件保存当日产量列号
#define XLSSAVESSLCOL 4   //文件保存累计产量列号
#define XLSSAVEPROCOL 5   //文件保存当日销量列号
#define XLSSAVESPRCOL 6   //文件保存累计销量列号
#define XLSSAVESTKCOL 7   //文件保存期末库存列号
#define XLSSAVETRACOL 8   //文件保存铁路运输列号
#define XLSSAVECARCOL 9   //文件保存汽车运输列号
#define XLSSAVEREMCOL 10  //文件保存销量备注列号

#endif // COMMON_H
