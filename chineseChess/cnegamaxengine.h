#ifndef CNEGAMAXENGINE_H
#define CNEGAMAXENGINE_H

#include "commfunc.h"
#include "CSearchEngine.h"

//搜索引擎. 使用负极大值方法 由CSearchEngine派生来
class CNegaMaxEngine : public CSearchEngine
{
public:
        CNegaMaxEngine();
        virtual ~CNegaMaxEngine();
        //用以找出给定局面的下一步走法
        virtual void SearchAGoodMove(int position[10][9]);

protected:
        int NegaMax(int depth);	//负极大值搜索引擎
};

#endif // CNEGAMAXENGINE_H
