// MoveGenerator.cpp: implementation of the CMoveGenerator class
#include <cstdlib>
#include "CMoveGenerator.h"


// Construction/Destruction
// 构造函数
CMoveGenerator::CMoveGenerator()
{
}

// 析构函数
CMoveGenerator::~CMoveGenerator()
{
}

// 判断局面position上，从From到To的走法是否合法
// 如果是合法走法，返回TRUE，否则返回false
bool CMoveGenerator::IsValidMove(BYTE position[10][9], int nFromX, int nFromY, int nToX, int nToY)
{
    int i, j;
    int nMoveChessID, nTargetID;

    if (nFromY == nToY && nFromX == nToX)
        return false; // 目的与源相同，非法

    nMoveChessID = position[nFromY][nFromX];
    nTargetID = position[nToY][nToX];

    if (IsSameSide(nMoveChessID, nTargetID))
        return false; // 吃自己的棋，非法

    switch (nMoveChessID)
    {
    case B_KING:
        // 判断是否老将见面
        if (nTargetID == R_KING)
        {
            if (nFromX != nToX)
                    return false; // 两个将不在同一列
            for (i = nFromY + 1; i < nToY; i++)
                if (position[i][nFromX] != NOTHING)
                        return false; // 中间隔有棋子，返回false
        }
        else
        {
            // 目标点在九宫之外
            if (nToY > 2 || nToX > 5 || nToX < 3)
                 return false;
            // 将帅只走一步直线
            if (abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
                 return false;
        }
        break;

    case R_KING: // 红将
        // 判断是否老将见面
        if (nTargetID == B_KING)
        {
            if (nFromX != nToX)
                    return false; // 两个将不在同一列
            for (i = nFromY - 1; i > nToY; i--)
                if (position[i][nFromX] != NOTHING)
                        return false; // 中间隔有棋子，返回false
        }
        else
        {
            // 目标点在九宫之外
            if (nToY < 7 || nToX > 5 || nToX < 3)
                 return false;
            // 将帅只走一步直线
            if (abs(nFromY - nToY) + abs(nToX - nFromX) > 1)
                 return false;
        }
        break;

    case R_BISHOP: // 红仕
        // 仕出九宫
        if (nToY < 7 || nToX > 5 || nToX < 3)
              return false;
        // 仕走斜线
        if (abs(nFromY - nToY) != 1 || abs(nToX - nFromX) != 1)
              return false;
        break;

    case B_BISHOP: // 黑士
        // 士出九宫
        if (nToY > 2 || nToX > 5 || nToX < 3)
              return false;
        // 士走斜线
        if (abs(nFromY - nToY) != 1 || abs(nToX - nFromX) != 1)
              return false;
        break;

    case R_ELEPHANT: // 红相
        // 相不能过河
        if (nToY < 5)
              return false;
        // 相走田字
        if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
              return false;
        // 相眼被塞住了
        if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOTHING)
              return false;
        break;

    case B_ELEPHANT: // 黑象
        // 象不能过河
        if (nToY > 4)
              return false;
        // 象走田字
        if (abs(nFromX - nToX) != 2 || abs(nFromY - nToY) != 2)
              return false;
        // 象眼被塞住了
        if (position[(nFromY + nToY) / 2][(nFromX + nToX) / 2] != NOTHING)
              return false;
        break;

    case B_PAWN: // 黑兵
        // 兵不回头
        if (nToY < nFromY)
              return false;
        // 兵过河前只能直走
        if (nFromY < 5 && nFromY == nToY)
              return false;
        // 兵只走一步直线
        if (nToY - nFromY + abs(nToX - nFromX) > 1)
              return false;
        break;

    case R_PAWN: // 红卒
        // 卒不回头
        if (nToY > nFromY)
              return false;
        // 卒过河前只能直走
        if (nFromY > 4 && nFromY == nToY)
              return false;
        // 卒只走一步直线
        if (nFromY - nToY + abs(nToX - nFromX) > 1)
              return false;
        break;

    case B_CAR: // 黑車
    case R_CAR: // 红車
        // 車走直线
        if (nFromY != nToY && nFromX != nToX)
                return false;

        if (nFromY == nToY) // 横向
        {
            if (nFromX < nToX) // 向右
            {
                for (i = nFromX + 1; i < nToX; i++)
                    if (position[nFromY][i] != NOTHING)
                        return false;
            }
            else // 向左
            {
                for (i = nToX + 1; i < nFromX; i++)
                    if (position[nFromY][i] != NOTHING)
                        return false;
            }
        }
        else // 纵向
        {
            if (nFromY < nToY) // 向下
            {
                for (j = nFromY + 1; j < nToY; j++)
                    if (position[j][nFromX] != NOTHING)
                        return false;
            }
            else // 向上
            {
                for (j = nToY + 1; j < nFromY; j++)
                    if (position[j][nFromX] != NOTHING)
                        return false;
            }
        }
        break;

    case B_HORSE: // 黑馬
    case R_HORSE: // 红馬
        // 馬走日字
        if (!((abs(nToX - nFromX) == 1 && abs(nToY - nFromY) == 2) || 
              (abs(nToX - nFromX) == 2 && abs(nToY - nFromY) == 1)))
                return false;

        if (nToX - nFromX == 2) // 横向右走
        {
            i = nFromX + 1;
            j = nFromY;
        }
        else if (nFromX - nToX == 2) // 横向左
        {
            i = nFromX - 1;
            j = nFromY;
        }
        else if (nToY - nFromY == 2) // 纵向下
        {
            i = nFromX;
            j = nFromY + 1;
        }
        else if (nFromY - nToY == 2) // 纵向上
        {
            i = nFromX;
            j = nFromY - 1;
        }

        // 绊馬腿
        if (position[j][i] != NOTHING)
            return false;
        break;

    case B_CANNON: // 黑炮
    case R_CANNON: // 红炮
        // 炮走直线
        if (nFromY != nToY && nFromX != nToX)
                return false;

        // 炮不吃子时经过的路线中不能有棋子
        if (position[nToY][nToX] == NOTHING)
        {
            if (nFromY == nToY) // 横向
            {
                if (nFromX < nToX) // 向右
                {
                    for (i = nFromX + 1; i < nToX; i++)
                        if (position[nFromY][i] != NOTHING)
                            return false;
                }
                else // 向左
                {
                    for (i = nToX + 1; i < nFromX; i++)
                        if (position[nFromY][i] != NOTHING)
                            return false;
                }
            }
            else // 纵向
            {
                if (nFromY < nToY) // 向下
                {
                    for (j = nFromY + 1; j < nToY; j++)
                        if (position[j][nFromX] != NOTHING)
                            return false;
                }
                else // 向上
                {
                    for (j = nToY + 1; j < nFromY; j++)
                        if (position[j][nFromX] != NOTHING)
                            return false;
                }
            }
        }
        // 炮吃子时
        else
        {
            int count = 0;
            if (nFromY == nToY) // 横向
            {
                if (nFromX < nToX) // 向右
                {
                    for (i = nFromX + 1; i < nToX; i++)
                    {
                        if (position[nFromY][i] != NOTHING)
                            count++;
                    }
                        if (count != 1) return false;
                }
                else // 向左
                {
                    for (i = nToX + 1; i < nFromX; i++)
                    {
                        if (position[nFromY][i] != NOTHING)
                            count++;
                    }
                        if (count != 1) return false;
                }
            }
            else // 纵向
            {
                if (nFromY < nToY) // 向下
                {
                    for (j = nFromY + 1; j < nToY; j++)
                    {
                        if (position[j][nFromX] != NOTHING)
                            count++;
                    }
                        if (count != 1) return false;
                }
                else // 向上
                {
                    for (j = nToY + 1; j < nFromY; j++)
                    {
                        if (position[j][nFromX] != NOTHING)
                            count++;
                    }
                        if (count != 1) return false;
                }
            }
        }
        break;

    default:
        return false;
    }

    return true; // 合法的走法，返回true
}
// 在m_MoveList中插入一个走法
int CMoveGenerator::AddMove(int nFromX, int nFromY, int nToX, int nToY, int nPlay)
{
    m_MoveList[nPlay][m_nMoveCount].From.x = nFromX;
    m_MoveList[nPlay][m_nMoveCount].From.y = nFromY;
    m_MoveList[nPlay][m_nMoveCount].To.x = nToX;
    m_MoveList[nPlay][m_nMoveCount].To.y = nToY;
    m_nMoveCount++;
    return m_nMoveCount;
}

// 用以产生局面position中所有可能的走法
// position是包含所有棋子位置信息的二维数组
// nPlay指明当前搜索的层数，每层将走法存在不同的位置，以免覆盖
// nSide指明产生哪一方的走法，TRUE为红方，false是黑方
int CMoveGenerator::CreatePossibleMove(BYTE position[10][9], int nPlay, int nSide)
{
    int x, y, nChessID;
    int i, j;

    m_nMoveCount = 0;

    for (j = 0; j < 9; j++)
        for (i = 0; i < 10; i++)
        {
            if (position[i][j] != NOTHING)
            {
                nChessID = position[i][j];
                // 如要产生黑棋走法，跳过红棋
                if (!nSide && IsRed(nChessID))
                    continue;
                // 如要产生红棋走法，跳过黑棋
                if (nSide && IsBlack(nChessID))
                    continue;

                switch (nChessID)
                {
                case R_KING: // 红将
                case B_KING: // 黑帅
                    Gen_KingMove(position, i, j, nPlay);
                    break;

                case R_BISHOP: // 红仕
                    Gen_RBishopMove(position, i, j, nPlay);
                    break;

                case B_BISHOP: // 黑士
                    Gen_BBishopMove(position, i, j, nPlay);
                    break;

                case R_ELEPHANT: // 红相
                case B_ELEPHANT: // 黑象
                    Gen_ElephantMove(position, i, j, nPlay);
                    break;

                case R_HORSE: // 红馬
                case B_HORSE: // 黑馬
                    Gen_HorseMove(position, i, j, nPlay);
                    break;

                case R_CAR: // 红車
                case B_CAR: // 黑車
                    Gen_CarMove(position, i, j, nPlay);
                    break;

                case R_PAWN: // 红卒
                    Gen_RPawnMove(position, i, j, nPlay);
                    break;

                case B_PAWN: // 黑兵
                    Gen_BPawnMove(position, i, j, nPlay);
                    break;

                case B_CANNON: // 黑炮
                case R_CANNON: // 红炮
                    Gen_CannonMove(position, i, j, nPlay);
                    break;

                default:
                    break;
                } // end of switch
            }
        }

    return m_nMoveCount; // 返回总的走法数
}

// 产生王的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_KingMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;

    // 黑帅九宫（0-2行，3-5列）
    for (y = 0; y < 3; y++)
        for (x = 3; x < 6; x++)
            if (IsValidMove(position, j, i, x, y)) // 走步是否合法
                AddMove(j, i, x, y, nPlay); // 将这个走法插入m_MoveList

    // 红将九宫（7-9行，3-5列）
    for (y = 7; y < 10; y++)
        for (x = 3; x < 6; x++)
            if (IsValidMove(position, j, i, x, y)) // 走步是否合法
                AddMove(j, i, x, y, nPlay); // 将这个走法插入m_MoveList
}

// 产生红仕的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_RBishopMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;

    // 红仕九宫（7-9行，3-5列）
    for (y = 7; y < 10; y++)
        for (x = 3; x < 6; x++)
            if (IsValidMove(position, j, i, x, y)) // 走步是否合法
                AddMove(j, i, x, y, nPlay); // 将这个走法插入m_MoveList
}

// 产生黑士的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_BBishopMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;

    // 黑士九宫（0-2行，3-5列）
    for (y = 0; y < 3; y++)
        for (x = 3; x < 6; x++)
            if (IsValidMove(position, j, i, x, y)) // 走步是否合法
                AddMove(j, i, x, y, nPlay); // 将这个走法插入m_MoveList
}

// 产生象/相的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_ElephantMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;

    // 插入右下方的有效走法（右2下2）
    x = j + 2;
    y = i + 2;
    if (x < 9 && y < 10 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 插入右上方的有效走法（右2上2）
    x = j + 2;
    y = i - 2;
    if (x < 9 && y >= 0 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 插入左下方的有效走法（左2下2）
    x = j - 2;
    y = i + 2;
    if (x >= 0 && y < 10 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 插入左上方的有效走法（左2上2）
    x = j - 2;
    y = i - 2;
    if (x >= 0 && y >= 0 && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);
}

// 产生馬的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_HorseMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;

    // 右2下1
    x = j + 2;
    y = i + 1;
    if ((x < 9 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 右2上1
    x = j + 2;
    y = i - 1;
    if ((x < 9 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 左2下1
    x = j - 2;
    y = i + 1;
    if ((x >= 0 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 左2上1
    x = j - 2;
    y = i - 1;
    if ((x >= 0 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 右1下2
    x = j + 1;
    y = i + 2;
    if ((x < 9 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 左1下2
    x = j - 1;
    y = i + 2;
    if ((x >= 0 && y < 10) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 右1上2
    x = j + 1;
    y = i - 2;
    if ((x < 9 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);

    // 左1上2
    x = j - 1;
    y = i - 2;
    if ((x >= 0 && y >= 0) && IsValidMove(position, j, i, x, y))
        AddMove(j, i, x, y, nPlay);
}

// 产生红卒的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_RPawnMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;
    int nChessID;

    nChessID = position[i][j];

    // 向前（上）走
    y = i - 1;
    x = j;
    if (y > 0 && !IsSameSide(nChessID, position[y][x]))
        AddMove(j, i, x, y, nPlay); // 前方无阻碍，插入走法

    // 是否已过河（红卒过河线为第5行，i<5表示过河）
    if (i < 5)
    {
        // 向右横走
        y = i;
        x = j + 1;
        if (x < 9 && !IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPlay); // 插入向右的走法

        // 向左横走
        x = j - 1;
        if (x >= 0 && !IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPlay); // 插入向左的走法
    }
}

// 产生黑兵的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_BPawnMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;
    int nChessID;

    nChessID = position[i][j];

    // 向前（下）走
    y = i + 1;
    x = j;
    if (y < 10 && !IsSameSide(nChessID, position[y][x]))
        AddMove(j, i, x, y, nPlay); // 插入向前的走法

    // 是否已过河（黑兵过河线为第4行，i>4表示过河）
    if (i > 4)
    {
        // 向右横走
        y = i;
        x = j + 1;
        if (x < 9 && !IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPlay); // 插入向右的走法

        // 向左横走
        x = j - 1;
        if (x >= 0 && !IsSameSide(nChessID, position[y][x]))
            AddMove(j, i, x, y, nPlay); // 插入向左的走法
    }
}

// 产生車的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_CarMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;
    int nChessID;

    nChessID = position[i][j];

    // 插入右边的可走位置
    x = j + 1;
    y = i;
    while (x < 9)
    {
        if (position[y][x] == NOTHING)
            AddMove(j, i, x, y, nPlay);
        else
        {
            if (!IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPlay);
            break;
        }
        x++;
    }

    // 插入左边的可走位置
    x = j - 1;
    y = i;
    while (x >= 0)
    {
        if (position[y][x] == NOTHING)
            AddMove(j, i, x, y, nPlay);
        else
        {
            if (!IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPlay);
            break;
        }
        x--;
    }

    // 插入向下的可走位置
    x = j;
    y = i + 1;
    while (y < 10)
    {
        if (position[y][x] == NOTHING)
            AddMove(j, i, x, y, nPlay);
        else
        {
            if (!IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPlay);
            break;
        }
        y++;
    }

    // 插入向上的可走位置
    x = j;
    y = i - 1;
    while (y >= 0)
    {
        if (position[y][x] == NOTHING)
            AddMove(j, i, x, y, nPlay);
        else
        {
            if (!IsSameSide(nChessID, position[y][x]))
                AddMove(j, i, x, y, nPlay);
            break;
        }
        y--;
    }
}

// 产生炮的合法走步
// i,j表明棋子的位置
// nPlay表明插入到List第几层
void CMoveGenerator::Gen_CannonMove(BYTE position[10][9], int i, int j, int nPlay)
{
    int x, y;
    bool flag;
    int nChessID;

    nChessID = position[i][j];

    // 插入向右方向上的可走位置
    x = j + 1;
    y = i;
    flag = false;
    while (x < 9)
    {
        if (position[y][x] == NOTHING) // 此位置上没有棋子
        {
            if (!flag) // 没有隔棋子
                AddMove(j, i, x, y, nPlay); // 插入可走位置
        }
        else
        {
            if (!flag) // 没有隔棋子，此棋子是第一个阻碍，设置标志
                flag = true;
            else // 隔有棋子，此处如为敌方棋子就可走
            {
                if (!IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPlay);
                break;
            }
        }
        x++; // 继续下一个位置
    }

    // 插入向左方向上的可走位置
    x = j - 1;
    y = i;
    flag = false;
    while (x >= 0)
    {
        if (position[y][x] == NOTHING) // 此位置上没有棋子
        {
            if (!flag) // 此位置是否同炮之间没有阻碍
                AddMove(j, i, x, y, nPlay); // 插入可走位置
        }
        else
        {
            if (!flag) // 没有隔棋子，此棋子是第一个阻碍，设置标志
                flag = true;
            else // 隔有棋子，此处如为敌方棋子就可走
            {
                if (!IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPlay); // 是敌方棋子，可走
                break;
            }
        }
        x--; // 继续下一个位置
    }

    // 插入向下方向上的可走位置
    x = j;
    y = i + 1;
    flag = false;
    while (y < 10)
    {
        if (position[y][x] == NOTHING)
        {
            if (!flag)
                AddMove(j, i, x, y, nPlay);
        }
        else
        {
            if (!flag) // 没有隔棋子，此棋子是第一个阻碍，设置标志
                flag = true;
            else // 隔有棋子，此处如为敌方棋子就可走
            {
                if (!IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPlay); // 是敌方棋子，可走
                break;
            }
        }
        y++;
    }

    // 插入向上方向上的可走位置
    x = j;
    y = i - 1;
    flag = false;
    while (y >= 0)
    {
        if (position[y][x] == NOTHING)
        {
            if (!flag)
                AddMove(j, i, x, y, nPlay);
        }
        else
        {
            if (!flag)
                flag = true;
            else
            {
                if (!IsSameSide(nChessID, position[y][x]))
                    AddMove(j, i, x, y, nPlay);
                break;
            }
        }
        y--;
    }
}
