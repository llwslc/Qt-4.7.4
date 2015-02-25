#include "cnegamaxengine.h"

CNegaMaxEngine::CNegaMaxEngine()
{

}

CNegaMaxEngine::~CNegaMaxEngine()
{

}
//此函数指针对传入的position找出一步最佳算法
//并修改棋盘数据为走过的状态
void CNegaMaxEngine::SearchAGoodMove(int position[10][9])
{
    //设定搜索层数为 m_nSearchDepth
    m_nMaxDepth = 2; //搜索层数为2
    //将传入的棋盘复制到成员变量
    memcpy(CurPosition, position, 4*90);
    //调用负极大值搜索函数找最佳走法
    NegaMax(m_nMaxDepth);
    MakeMove(&m_cmBestMove);
    //将修改过的棋盘复制到传入的棋盘,传出
    memcpy(position, CurPosition, 4*90);
}

//负极大值搜索函数
//depth表示节点里叶子节点的层数
int CNegaMaxEngine::NegaMax(int depth)
{
    int current = -20000;
    int score;
    long Count,i;
    int type;
    i = IsGameOver(CurPosition, depth);	//检查棋局是否结束
    if(i != 0)
        return i;	//棋局结束,返回极大/极小值
    if(depth <= 0)	//叶子节点取估值
        //返回估值
        return m_pEval->Eveluate(CurPosition, (m_nMaxDepth - depth) % 2);
    //列举出当前局面下一步所有可能的走法
    Count = m_pMG->CreatePossibleMove(CurPosition, depth, (m_nMaxDepth - depth) % 2);
    for(i = 0; i < Count; i++)
    {
        //根据走法产生新局面
        type = MakeMove(&m_pMG->m_MoveList[depth][i]);
        //递归调用付极大值搜索下一层的节点
        score = -NegaMax(depth - 1);
        //恢复当前局面
        UnMakeMove(&m_pMG->m_MoveList[depth][i],type);
        if(score > current)	//如果score大于已知的最大值
        {
            current = score;	//修改当前最大值为score;
            if(depth == m_nMaxDepth)
            {
                //靠近根部时保存最佳走法
                m_cmBestMove = m_pMG->m_MoveList[depth][i];
            }
        }
    }
    return current;	//返回极大值
}
