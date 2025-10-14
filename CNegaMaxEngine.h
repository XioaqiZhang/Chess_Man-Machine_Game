// NegaMaxEngine.h: interface for the CNegaMaxEngine class
#ifndef CNEGAMAXENGINE_H
#define CNEGAMAXENGINE_H

#include "CSearchEngine.h"

class CNegaMaxEngine : public CSearchEngine
{
public:
    CNegaMaxEngine();
    virtual ~CNegaMaxEngine();

    // 用以找出给定局面的下一步的走法
    virtual void SearchAGoodMove(BYTE position[10][9]);

protected:
    // 负极大值搜索引擎
    int NegaMax(int depth);
};

#endif // !defined(AFX_NEGAMAXENGINE_H__6C3A4902_CDED_11D5_AEC7_5254A62E22C7__INCLUDED_)
