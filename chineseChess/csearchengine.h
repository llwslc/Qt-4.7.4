#ifndef CSEARCHENGINE_H
#define CSEARCHENGINE_H

#include "commfunc.h"
#include "CMoveGenerator.h"
#include "CEveluation.h"

//搜索引擎的基类 .定义接口及公共函数.
class CSearchEngine
{
public:
        CSearchEngine();
        virtual ~CSearchEngine();
        //博弈接口,为当前局面走出下一步棋
        virtual void SearchAGoodMove(int position[10][9])=0;
        //设定最大搜索深度
        virtual void SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
        //设计估值引擎
        virtual void SetEveluator(CEveluation *pEval){m_pEval = pEval;};
        //设定走法产生器
        virtual void SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};

protected:
        //根据某一走法产生走了以后的棋盘
        virtual int MakeMove(CHESSMOVE* move);
        //恢复某一走法所产生棋盘为走过之前的
        virtual void UnMakeMove(CHESSMOVE* move,int type);
        //用于判断当前局面是否已经分出胜负
        virtual int IsGameOver(int position[10][9], int nDepth);
        //搜索用于当前节点棋盘状态的数组
        int CurPosition[10][9];
        //记录最佳走法的变量
        CHESSMOVE m_cmBestMove;
        //走法产生器指针
        CMoveGenerator *m_pMG;
        //估值核心指针
        CEveluation *m_pEval;
        //最大搜索深度
        int m_nSearchDepth;
        //当前搜索的最大搜索深度
        int m_nMaxDepth;

};

#endif // CSEARCHENGINE_H
