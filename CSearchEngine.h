// SearchEngine.h: interface for the CSearchEngine class
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

    // 设定最大搜索深度
    void SetSearchDepth(int nDepth) { m_nSearchDepth = nDepth; };

    // 设定估值引擎
    void SetEvaluator(CEveluation* pEval) { m_pEval = pEval; };

    // 设定走法产生器
    void SetMoveGenerator(CMoveGenerator* pMG) { m_pMG = pMG; };

protected:
    // 根据某一走法产生走了之后的棋盘
    BYTE MakeMove(CHESSMOVE move);

    // 恢复某一走法所产生棋盘为走过之前的
    void UnMakeMove(CHESSMOVE move, BYTE type);

    // 用于判断当前局面是否已分出胜负
    int IsGameOver(BYTE position[10][9], int nDepth);

    // 搜索时用于当前节点棋盘状态的数组
    BYTE m_CurPosition[10][9];

    // 记录最佳走法的变量
    CHESSMOVE m_cmBestMove;

    // 走法产生器指针
    CMoveGenerator* m_pMG;

    // 估值核心指针
    CEveluation* m_pEval;

    // 最大搜索深度
    int m_nSearchDepth;

    // 当前搜索的最大搜索深度
    int m_nMaxDepth;
};

#endif // CSEARCHENGINE_H
