#include "CNegaMaxEngine.h"
#include <memory>
#include <cstring>

CNegaMaxEngine::CNegaMaxEngine()
{
}

CNegaMaxEngine::~CNegaMaxEngine()
{
}

void CNegaMaxEngine::SearchAGoodMove(BYTE position[10][9])
{
   // 设定搜索层数
   m_nMaxDepth = m_nSearchDepth;
    // 保存当前局面
    memcpy(CurPosition, position, 90);
    // 调用NegaMax搜索最佳走法
    NegaMax(m_nMaxDepth);
    // 将棋盘修改为走过的
    MakeMove(&m_cmBestMove);
    // 将走法输出
    memcpy(position, CurPosition, 90);

}

int CNegaMaxEngine::NegaMax(int depth)
{
    int current = -20000;
    int score;
    int count, i;
    BYTE type;
    i = IsGameOver(CurPosition, depth);
    if (i != 0)
    {
        return i;
    }
    if (depth <= 0)
    {
        return m_pEval->Eveluate(CurPosition, (m_nMaxDepth - depth) % 2);
    }
    count = m_pMG->CreatepossibleMove(CurPosition, depth, (m_nMaxDepth - depth) % 2);
    for (i = 0; i < count; i++)
    {
        // 根据走法产生新局面
        type = MakeMove(&m_pMG->m_MoveList[depth][i]);
        // 递归调用NegaMax
        score = -NegaMax(depth - 1);
        // 恢复当前局面
        UnMakeMove(&m_pMG->m_MoveList[depth][i], type);
        if (score > current)
        {
            current = score;
            if (depth == m_nMaxDepth)
            {
                // 如果是根节点，记录最佳走法
                m_cmBestMove = m_pMG->m_MoveList[depth][i];
            }
        }
    }
    return current;
}