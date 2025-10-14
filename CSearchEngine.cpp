// SearchEngine.cpp: implementation of the CSearchEngine class
#include <cstring>
#include "CSearchEngine.h"

// Construction/Destruction
CSearchEngine::CSearchEngine()
{
    m_pMG = nullptr;
    m_pEval = nullptr;
    m_nSearchDepth = 4;
    m_nMaxDepth = 0;
}

CSearchEngine::~CSearchEngine()
{
    // Note: m_pMG and m_pEval are non-owning; lifetime managed by caller
}

// 根据传入的走法改变棋盘
// move是要进行的走法
BYTE CSearchEngine::MakeMove(CHESSMOVE move)
{
    BYTE nChessID;

    // 取目标位置棋子
    nChessID = m_CurPosition[move.To.y][move.To.x];

    // 把棋子移动到目标位置
    m_CurPosition[move.To.y][move.To.x] = m_CurPosition[move.From.y][move.From.x];

    // 将原位置清空
    m_CurPosition[move.From.y][move.From.x] = NOTHING;

    return nChessID; // 返回被吃掉的棋子
}

// 根据传入的走法恢复棋盘
// move是要恢复的走法
// nChessID是原棋盘上move目标位置的棋子类型
void CSearchEngine::UnMakeMove(CHESSMOVE move, BYTE nChessID)
{
    // 将目标位置棋子拷回原位
    m_CurPosition[move.From.y][move.From.x] = m_CurPosition[move.To.y][move.To.x];

    // 恢复目标位置的棋子
    m_CurPosition[move.To.y][move.To.x] = nChessID;
}

// 用以检查给定局面游戏是否结束
// 如未结束，返回0，否则返回极大/极小值
int CSearchEngine::IsGameOver(BYTE position[10][9], int nDepth)
{
    int i, j;
    bool RedLive = false, BlackLive = false;

    // 检查红方九宫是否有将帅
    for (i = 7; i < 10; i++)
        for (j = 3; j < 6; j++)
        {
            if (position[i][j] == R_KING)
                RedLive = true;
        }

    // 检查黑方九宫是否有将帅
    for (i = 0; i < 3; i++)
        for (j = 3; j < 6; j++)
        {
            if (position[i][j] == B_KING)
                BlackLive = true;
        }

    // 取当前是奇偶标志（判断当前层是极大层还是极小层）
    i = (m_nMaxDepth - nDepth + 1) % 2;

    if (!RedLive) // 红将不在了
    {
        if (i)
            return 19990 + nDepth; // 奇数层（极大层）返回极大值
        else
            return -19990 - nDepth; // 偶数层（极小层）返回极小值
    }

    if (!BlackLive) // 黑帅不在了
    {
        if (i)
            return -19990 - nDepth; // 奇数层返回极小值
        else
            return 19990 + nDepth; // 偶数层返回极大值
    }

    return 0; // 两个将都在，返回零
}
