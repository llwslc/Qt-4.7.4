#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "common.h"
#include "listdialog.h"
#include "recorddialog.h"
#include "chatdialog.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void paintEvent(QPaintEvent *); //绘图
    void mousePressEvent(QMouseEvent *event); //鼠标压下
    void randomp(); //随机生成地图
    void initPixmaps(); //生成棋子序列
    bool matchChessman(); //匹配棋子
    void gameLevelSetValue(); //根据等级赋值
    bool matchDirect(chessman preManTmp, chessman nextManTmp); //直接连接
    bool matchOneCorner(chessman preManTmp, chessman nextManTmp); //一个拐角相连
    bool matchTwoCorner(chessman preManTmp, chessman nextManTmp); //两个拐点相连

    int gameLevel; //游戏等级
    int manNum; //棋盘棋子个数
    int manTypeNum; //棋盘棋子类型数目
    int manWide; //棋子宽度
    int manHigh; //棋子高度
    QList<QPixmap> pixmaps; //图片列表
    QPixmap backgroundPixmap; //背景图
    bool gamePause; //暂停标志
    bool gameStart; //开始标志
    bool gameOver; //结束标志
    int gameOnline; //联机游戏标志,0 单机, 1 发起者, 2 同意者
    chessman preMan; //前一个棋子选择
    chessman nextMan; //后一个棋子选择
    int manSum;    //游戏棋子总数
    int manLeft;   //游戏剩余棋子

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void gameOnlineRandomp();

    void gameOnlineLevel();

    void gameOnlineServer();

    void gameOnlineClient();

    void gameOnlineProgressBar();

    void gameOnlineGameOver();

    void gamePlayerOne();

    void gamePlayerTwo();

private:
    Ui::Dialog *ui;
    listDialog listDlg;
    recordDialog recordDlg;
    ChatDialog chatDlg;
};

#endif // DIALOG_H
