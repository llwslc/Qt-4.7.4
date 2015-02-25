#ifndef COMMFUNC_H
#define COMMFUNC_H

#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>
#include <QHash>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QListWidgetItem>

#define NOCHESS			0 //没有棋子

#define B_KING			1 //黑帅
#define B_CAR			2 //黑车
#define B_HORSE			3 //黑马
#define B_CANON			4 //黑炮
#define B_BISHOP		5 //黑士
#define B_ELEPHANT		6 //黑象
#define B_PAWN			7 //黑兵
#define B_BEGIN			B_KING
#define B_END			B_PAWN

#define R_KING			8 //红帅
#define R_CAR			9 //红车
#define R_HORSE			10//红马
#define R_CANON			11//红炮
#define R_BISHOP		12//红士
#define R_ELEPHANT		13//红相
#define R_PAWN			14//红卒
#define R_BEGIN			R_KING
#define R_END			R_PAWN

#define IsBlack(x)	(x >= B_BEGIN && x <= B_END)	//判断一个棋子是不是黑色
#define IsRed(x)	(x >= R_BEGIN && x <= R_END)	//判断一个棋子是不是红色

//判断两个棋子是不是同色
#define IsSameSide(x,y)  ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))

//定义一个棋子位置的结构
typedef struct _chessmanposition
{
    int x;
    int y;
}CHESSMANPOS;

//一个走法的结构
typedef struct _chessmove
{
    int ChessID;	//表明是什么棋子
    CHESSMANPOS From; //起始位置
    CHESSMANPOS To; //走到位置
}CHESSMOVE;

//正在移动的棋子
typedef struct _movechess
{
    int nChessID;
    QPoint ptMovePoint;
}MOVECHESS;

#define BOARDSTARTX 30 //棋盘起始X
#define BOARDSTARTY 30 //棋盘起始Y
#define BOARDMANX 10 //棋盘棋子点起始X
#define BOARDMANY 10 //棋盘棋子点起始Y
#define BOARDWIDTH 460 //棋盘宽度
#define BOARDHEIGHT 510 //棋盘高度
#define GRILLEWIDTH 40 //棋盘上每个格子的高度
#define GRILLEHEIGHT 40 //棋盘上每个格子的宽度

//定义常量保存棋盘的初始状态
const int InitChessBoard[10][9]=
{
    {B_CAR,   B_HORSE, B_ELEPHANT, B_BISHOP, B_KING,  B_BISHOP, B_ELEPHANT, B_HORSE, B_CAR},
    {NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
    {NOCHESS, B_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    B_CANON, NOCHESS},
    {B_PAWN,  NOCHESS, B_PAWN,     NOCHESS,  B_PAWN,  NOCHESS,  B_PAWN,     NOCHESS, B_PAWN},
    {NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},

    {NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
    {R_PAWN,  NOCHESS, R_PAWN,     NOCHESS,  R_PAWN,  NOCHESS,  R_PAWN,     NOCHESS, R_PAWN},
    {NOCHESS, R_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    R_CANON, NOCHESS},
    {NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
    {R_CAR,   R_HORSE, R_ELEPHANT, R_BISHOP, R_KING,  R_BISHOP, R_ELEPHANT, R_HORSE, R_CAR}
};

//游戏结束,0:未结束,1:电脑胜利,2:玩家胜利
extern int chessGameOver;

//创建文件夹
bool createFolder(const QString dir);

//数字转字母
#define NUMTOUNICODE 65
//将文件数据转成棋子数据
void chessmanDataFromFile(QString fileData, int chessmanData[10][9]);
//将棋子数据转成文件数据
QString chessmanDataToFile(const int chessmanData[10][9]);

//检查游戏是否结束
void gameIsOver(int position[10][9]);


#endif // COMMFUNC_H
