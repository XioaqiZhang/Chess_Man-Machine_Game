#include "CSearchEngine.h"

CSearchEngine::CSearchEngine()
{
}

CSearchEngine::~CSearchEngine()
{
    delete m_pMG;
    delete m_pEval;
}

// 根据某一走法产生走了之后的棋盘
// 返回值： 被吃掉的棋子
BYTE CSearchEngine::MakeMove(const CHESSMOVE* move)
{
    BYTE nChessID;
    // 取出目标位置的棋子
    nChessID = CurPosition[move->To.x][move->To.y];
    // 把棋子移动到目标位置
    CurPosition[move->To.x][move->To.y] = CurPosition[move->From.x][move->From.y];
    // 把原来位置的棋子清除
    CurPosition[move->From.x][move->From.y] = NOCHESS;
    return nChessID;
}

// 撤销某一走法，恢复棋盘
void CSearchEngine::UnMakeMove(const CHESSMOVE* move, BYTE nChessID)
{
    // 把目标位置的棋子移回原来的位置
    CurPosition[move->From.x][move->From.y] = CurPosition[move->To.x][move->To.y];
    // 把目标位置清除
    CurPosition[move->To.x][move->To.y] = nChessID;
}

// 判断当前局面是否已经结束
// 未结束返回0，否则返回极大值或极小值
int CSearchEngine::IsGameOver(BYTE position[10][9], int nDepth)
{
    int i, j;
    bool redLive = false, blackLive = false;
    // 判断红方九宫是否还有将帅
    for (i = 7; i < 10; i++)
    {
        for (j = 3; j < 6; j++)
        {
            if (position[i][j] == R_KING)
            {
                redLive = true;
                break;
            }
            if (position[i][j] == R_KING)
            {
                blackLive = true;
                break;
            }
        }
        if (redLive || blackLive)
        {
            break;
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 3; j < 6; j++)
        {
            if (position[i][j] == B_KING)
            {
                blackLive = true;
                break;
            }
            if (position[i][j] == R_KING)
            {
                redLive = true;
                break;
            }
        }
        if (blackLive || redLive)
        {
            break;
        }
    }
    // 取当前是奇偶
    i = (m_nMaxDepth - nDepth + 1) % 2;
    if (!redLive)
    {
        if (i)
        {
            // 奇数层返回极大值
            return 19990 + nDepth;
        }
        else
        {
            // 偶数层返回极小值
            return -19990 - nDepth;
        }
    }
    if (!blackLive)
    {
        if (i)
        {
            // 奇数层返回极小值
            return -19990 - nDepth;
        }
        else
        {
            // 偶数层返回极大值
            return 19990 + nDepth;
        }
    }
    // 两方将帅都存在，返回0
    return 0;
}

