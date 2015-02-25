#ifndef COMMON_H
#define COMMON_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

#include "mydatabase.h"

//拷贝文件
bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
//拷贝文件夹
bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
//创建文件夹
bool createFolder(const QString dir);

//计算日期差
int datedef(QString dateStr, int rule);
//是否闰年
int leap(int year);
//交换两个数据
void swapNum(int *pre, int *next);
//星期转数字
int weekToInt(QString weekStr);

//删除按钮存在的标志
extern int itemDelButtonFlag;

//窗口位置
extern QPoint windowsPos;

//列表双击得到的标题
extern QString viewTitle;

#endif // COMMON_H
