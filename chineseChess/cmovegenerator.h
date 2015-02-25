#ifndef CMOVEGENERATOR_H
#define CMOVEGENERATOR_H

#include "commfunc.h"

//走法产生器
class CMoveGenerator
{
public:
        CMoveGenerator();
        virtual ~CMoveGenerator();
        //用以检查一个走法是否合法的静态函数
        static bool IsValidMove(int position[10][9],int nFromX,
                                                        int nFromY,int nToX,int nToY);
        //产生给定棋盘上的所有合法的走法
        int CreatePossibleMove(int position[10][9],int nPly,int nSide);
        //存放CreatePossibleMove 产生所有走法的队列
        CHESSMOVE m_MoveList[8][80];

protected:
        //在m_MoveList中插入一个走法
        int AddMove(int nFromX,int nToX,int nFromY,int nToY,int nPly);
        //产生给定棋盘上的给定位置上的将/帅的走法
        void Gen_KingMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的红仕的走法
        void Gen_RBishopMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的黑士的走法
        void Gen_BBishopMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的相/象的走法
        void Gen_ElephantMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的马的走法
        void Gen_HorseMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的车的走法
        void Gen_CarMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的红卒的走法
        void Gen_RPawnMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的黑兵的走法
        void Gen_BPawnMove(int position[10][9],int i,int j,int nPly);
        //产生给定棋盘上的给定位置上的炮的走法
        void Gen_CanonMove(int position[10][9],int i,int j,int nPly);

        int m_nMoveCount;	//记录m_MoveList中走法的数量

};

#endif // CMOVEGENERATOR_H
