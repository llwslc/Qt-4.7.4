#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "commfunc.h"
#include "CMoveGenerator.h"
#include "CEveluation.h"
#include "CNegaMaxEngine.h"
#include "CSearchEngine.h"

namespace Ui {
    class mainWindow;
}

class mainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    void paintEvent(QPaintEvent *); //绘图
    void mousePressEvent(QMouseEvent *event); //鼠标压下
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);  //鼠标松开

    //定义棋盘数组.用于显示棋盘
    int m_ChessBoard[10][9];
    //备份棋盘数组.用于出错恢复
    int m_BackupChessBoard[10][9];
    //用于保存当前被拖拽的棋子的结构
    MOVECHESS m_MoveChess;
    //用与保存当前被拖拽的棋子的位置
    QPoint m_ptMoveChess;
    //用于显示棋盘
    QPixmap m_BoardBmp;
    //用户绘制棋子
    QPixmap m_Chessman;
    //棋子红黑标志
    bool chessmanRed;
    //搜索引擎指针
    CSearchEngine *m_pSE;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::mainWindow *ui;
};

#endif // MAINWINDOW_H
