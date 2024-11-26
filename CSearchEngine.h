#ifndef CSEARCHENGINE_H
#define CSEARCHENGINE_H

#include "define.h"
#include "CMoveGenerator.h"
#include "CEveluation.h"

class CSearchEngine
{
public:
    CSearchEngine();
    virtual ~CSearchEngine();
    // 博弈接口，为当前局面走出下一步
    virtual void SearchAGoodMove(BYTE position[10][9]) = 0;
    // 设置最大搜索深度
    void SetSearchDepth(int nDepth) { m_nMaxDepth = nDepth; }

protected:
    // 根据某一走法产生走了之后的棋盘
    BYTE MakeMove(const CHESSMOVE* move);
    // 撤销某一走法，恢复棋盘
    void UnMakeMove(const CHESSMOVE* move, BYTE nChessID);
    // 判断当前局面是否已经结束
    int IsGameOver(BYTE position[10][9], int nDepth);
    // 搜索时用于当前节点棋盘状态的数组
    BYTE CurPosition[10][9];
    // 记录最佳走法
    CHESSMOVE m_cmBestMove;
    // 走法产生器指针
    CMoveGenerator* m_pMG;
    // 估值核心指针
    CEveluation* m_pEval;
    // 最大搜索深度
    int m_nSearchDepth;
    // 当前搜索的最大深度
    int m_nMaxDepth;

};

#endif // CSEARCHENGINE_H
