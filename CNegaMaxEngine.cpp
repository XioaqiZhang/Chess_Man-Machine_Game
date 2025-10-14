// NegaMaxEngine.cpp: implementation of the CNegaMaxEngine class
#include <cstring>
#include "CNegaMaxEngine.h"

// Construction/Destruction
CNegaMaxEngine::CNegaMaxEngine()
{
}

CNegaMaxEngine::~CNegaMaxEngine()
{
}

// 此函数针对传入的position找出一步最佳走法
// 并修改棋盘数据为走过的状态
void CNegaMaxEngine::SearchAGoodMove(BYTE position[10][9])
{
    // 设定搜索层数为m_nSearchDepth
    m_nMaxDepth = m_nSearchDepth;

    // 将传入的棋盘复制到成员变量中
    std::memcpy(m_CurPosition, position, 90);

    // 调用负极大值搜索函数找最佳走法
    NegaMax(m_nMaxDepth);

    // 将棋盘修改为走过的
    MakeMove(m_cmBestMove);

    // 将修改过的棋盘复制到传入的棋盘中，传出
    std::memcpy(position, m_CurPosition, 90);
}

// 负极大值搜索函数
// depth表示节点离叶子节点的层数
int CNegaMaxEngine::NegaMax(int depth)
{
    int current = -20000;
    int score;
    int Count, i;
    BYTE type;

    // 检查棋局是否结束
    i = IsGameOver(m_CurPosition, depth);
    if (i != 0)
        return i; // 棋局结束，返回极大/极小值

    // 叶子节点取估值
    if (depth <= 0)
    return m_pEval->Evaluate(m_CurPosition, ((m_nMaxDepth - depth) % 2) != 0);

    // 列举出当前局面下一步所有可能的走法
    Count = m_pMG->CreatePossibleMove(m_CurPosition, depth, (m_nMaxDepth - depth) % 2);

    for (i = 0; i < Count; i++)
    {
        // 根据走法产生新局面
        type = MakeMove(m_pMG->m_MoveList[depth][i]);

        // 递归调用负极大值搜索下一层的节点
        score = -NegaMax(depth - 1);

        // 恢复当前局面
        UnMakeMove(m_pMG->m_MoveList[depth][i], type);

        // 如果score大于已知的最大值
        if (score > current)
        {
            current = score; // 修改当前最大值为score

            // 靠近根部时保存最佳走法
            if (depth == m_nMaxDepth)
            {
                m_cmBestMove = m_pMG->m_MoveList[depth][i];
            }
        }
    }

    return current; // 返回极大值
}
