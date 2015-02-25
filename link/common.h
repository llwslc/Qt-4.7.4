#ifndef COMMON_H
#define COMMON_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include <QAbstractSocket>
#include <QHash>
#include <QHostAddress>
#include <QString>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QUdpSocket>
#include <QTcpServer>
#include <QtNetwork>
#include <QListWidgetItem>

//游戏区域起始位置
#define GAMEAEROX 10
#define GAMEAEROY 10
//棋盘区域宽高
#define BOARDWIDE 500
#define BOARDHIGH 500
//点击选中后变小
#define REDUCEXY 5
//没有棋子
#define NOCHESSMAN 0
//等级棋子数目
#define LEVELONEMANNUM 10
#define LEVELONETYPENUM 10
#define LEVELTWOMANNUM 20
#define LEVELTWOTYPENUM 15
#define LEVELTHREEMANNUM 25
#define LEVELTHREETYPENUM 25
//数字转字母
#define NUMTOUNICODE 65

//游戏数据点
extern int **chessmanData;
//棋子的数据结构
class chessman
{
public:
    chessman();
    void clear();
    void set(int x=0, int y=0, int type=NOCHESSMAN);
    int getX();
    int getY();
    int getType();
    bool typeExist();
    friend bool operator ==(const chessman& a,const chessman& b);
private:
    int chessmanX;
    int chessmanY;
    int chessmanType;
};

//游戏时间
extern QTime gameTime;
//游戏类型
extern int gameRole;
//对方剩余棋子
extern int onlineManLeft;

//数据库
class database
{
public:
    database();
    bool opendb(QString dbname);
    void createtable();
    void closedb();
private:
    QSqlDatabase db;
};

//将消息转成棋子数据
void chessmanDataFromMessage(QString message);
//将棋子数据转成消息格式
QString chessmanDataToMessage();

#endif // COMMON_H
