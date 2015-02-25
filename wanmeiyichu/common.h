#ifndef COMMON_H
#define COMMON_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QtNetwork>
#include <QHash>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QSqlDatabase>
#include <QListWidgetItem>
#include <QStateMachine>
#include <QPushButton>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

//调试开关
#define DEBUGLEVELONE   1              //调试DEBUG开关等级1
#define DEBUGLEVELTWO   1              //调试DEBUG开关等级2
#define DEBUGLEVELTHREE 1              //调试DEBUG开关等级3

#define INTNUMBERINIT 0                //int类型数据初始化
#define NUMBERTOSTRINGBASE 10          //int转换string类型进制标志
#define INTNUMBERDECREMENT 1           //int类型数目自减1
#define INTEVENNUMBERFLAG 2            //int类型数字是否为偶数
#define STRINGNOTFINDINDEX -1          //在string中没有找到下标

#define WEATHERFINDSTRINGLENGTH 3      //天气预报中":"字段的长度

#define UPDATETIMEONESECOND 1*1000     //时间每秒更新
#define ISONLINETENSECONDS 10*1000     //网络每十秒诊断

#define BKGPAINTERX 0                  //背景绘制起始X位置
#define BKGPAINTERY 0                  //背景绘制起始Y位置

#define CLOTHESFONTSIZE 20             //衣服面板字体大小
#define DIGICLOCKDATEFONTSIZE 18       //天气预报地点字体大小
#define WEATHERPLACEFONTSIZE 72        //天气预报地点字体大小
#define WEATHERTEMPFONTSIZE 30         //天气预报温度字体大小

#define SQLCLOTHESIDNUMINDEX 0         //数据库衣服表中ID的索引位置
#define SQLCLOTHESNAMEINDEX 1          //数据库衣服表中名称的索引位置
#define SQLCLOTHESTYPEINDEX 2          //数据库衣服表中类型的索引位置
#define SQLCLOTHESSEASONINDEX 3        //数据库衣服表中季节的索引位置
#define SQLCLOTHESCLASSTYPEINDEX 4     //数据库衣服表中场合的索引位置
#define SQLCLOTHESBRANDINDEX 5         //数据库衣服表中品牌的索引位置
#define SQLCLOTHESPRICEINDEX 6         //数据库衣服表中价格的索引位置
#define SQLCLOTHESTIMEINDEX 7          //数据库衣服表中时间的索引位置
#define SQLCLOTHESSTOREPLACEINDEX 8    //数据库衣服表中存放地的索引位置
#define SQLCLOTHESBUYPLACEINDEX 9      //数据库衣服表中购买地的索引位置
#define SQLCLOTHESNOTEINDEX 10         //数据库衣服表中备注的索引位置
#define SQLCLOTHESPICPATHINDEX 11      //数据库衣服表中图片路径的索引位置

#define SQLDAYDRESSIDNUMINDEX 0        //数据库每日装扮表中ID的索引位置
#define SQLDAYDRESSCLOTHESIDINDEX 1    //数据库每日装扮表中衣服ID的索引位置
#define SQLDAYDRESSTYPEINDEX 2         //数据库每日装扮表中类型的索引位置
#define SQLDAYDRESSDATEINDEX 3         //数据库每日装扮表中日期的索引位置
#define SQLDAYDRESSPICPATHINDEX 4      //数据库每日装扮表中图片路径的索引位置

#define SQLWEATHERIDNUMINDEX 0         //数据库城市列表中ID的索引位置
#define SQLWEATHERCITYNAMEINDEX 1      //数据库城市列表中城市名称的索引位置
#define SQLWEATHERCITYCODEINDEX 2      //数据库城市列表中城市代码的索引位置

extern QPoint globaWindowsPos;         //窗口位置

extern QFont clothesFont;              //衣服窗口字体

extern QFont digiClockDateFont;        //主页日期字体

extern QFont weatherPlaceFont;         //天气预报地点字体

extern QFont weatherTempFont;          //天气预报温度字体

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
//创建文件夹
bool createFolder(const QString dir);

#endif // COMMON_H
