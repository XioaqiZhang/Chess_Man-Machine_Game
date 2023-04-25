#include "CMoveGenerator.h"
#include "define.h"
#include "math.h"
//构造函数
CMoveGenerator::CMoveGenerator()
{
}
//析构函数
CMoveGenerator::~CMoveGenerator()
{
}

//判断局面position上，从From到To的走法是否合法
//如果是合法走法，返回TRUE，否则返回FALSE
bool CMoveGenerator::IsValidMove(BYTE position[10][9],
                                 int nFromX, int nFromY, int nToX, int nToY)
{
    int nMoveChessID,nTargetID;
    int i,j;
    if((nFromX == nToX)&&(nFromY == nToY))
    {
        return false;//目的与源相同，非法
    }
    nMoveChessID = position[nFromX][nFromY];
    nTargetID = position[nToX][nToY];
    if(IsSameSide(nMoveChessID, nTargetID))
    {
        return false;//吃自己的棋，非法
    }

    switch(nMoveChessID)
    {
    case B_KING://黑将
        if(nTargetID == R_KING)//判断老将是否见面
        {
            if(nFromX != nToX)//横坐标不相等
            {
                return false;  //两将不在同一列
            }
            for(i = nFromY + 1; i < nToY; i++)
            {
                if(position[i][nFromY] != NOCHESS)//中间没有棋子
                {
                    return false;
                }
            }
        }
        else
        {
            if((nToX > 5) || (nToX < 3) || (nToY > 2))//目标点在将框之外
            {
                return false;
            }
            if((fabs(nFromX - nToX) + fabs(nFromY - nToY)) > 1)//将/帅走超过一步
            {
                return false;
            }
        }
        break;
    case R_KING://红帅
        if(nTargetID == B_KING)//判断老将是否见面
        {
            if(nFromX != nToX)//横坐标不相等
            {
                return false;//两将不在同一列
            }
            for(i = nFromY - 1; i > nToY; i--)
            {
                if(position[i][nFromY] != NOCHESS)//之间有棋子
                {
                    return false;
                }
            }
        }
        else
        {
            if((nToY > 5) || (nToY < 3) || (nToX < 7))//目标点在将框之外
            {
                return false;
            }
            if(fabs(nFromX - nToX) + fabs(nFromY - nToY) > 1)//将走超过1步
            {
                return false;
            }
        }
        break;
    case B_BISHOP://黑士
        if((nToX < 3) || (nToX > 5) || (nToY > 2))//目标点在将框外
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 1) || (fabs(nToY - nFromY) != 1))//士走斜线
        {
            return false;
        }
        break;
    case R_BISHOP://红士
        if((nToX < 3) || (nToX > 5) || (nToY < 7))//目标点在将框外
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 1) || (fabs(nToY - nFromY) != 1))//士走斜线
        {
            return false;
        }
        break;
    case B_ELEPHANT://黑象
        if(nToY > 4)//象不能过河
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 2) || (fabs(nToY - nFromY) != 2))//象走田字
        {
            return false;
        }
        if(position[(nFromX - nToX)/2][(nFromY - nToY)/2] != NOCHESS)//象眼被堵
        {
            return false;
        }
        break;
    case R_ELEPHANT://红相
        if(nToY < 5)//相不能过河
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 2) || (fabs(nToY - nFromY) != 2))//相走田字
        {
            return false;
        }
        if(position[(nFromX - nToX)/2][(nFromY - nToY)/2] != NOCHESS)//相眼被堵
        {
            return false;
        }
        break;
    case B_HORSE://黑马

    case R_HORSE://红马
        //马走日字
        if(!( ((fabs(nFromX - nToX)==2) && (fabs(nFromY - nToY)==1)) ||
              ((fabs(nFromX - nToX)==1) && (fabs(nFromY - nToY)==2))) )
        {
            return false;
        }
        if(nFromX - nToX == 2)
        {
            i = nFromX - 1;
            j = nFromY;
        }
        else if(nToX - nFromX == 2)
        {
            i = nFromX + 1;
            j = nFromY;
        }
        else if(nFromY - nToY == 2)
        {
            i = nFromX;
            j = nFromY - 1;
        }
        else if(nToY - nFromY == 2)
        {
            i = nFromX;
            j = nFromY + 1;
        }
        if(position[i][j] != NOCHESS)//拌马腿
        {
            return false;
        }
        break;
    case B_CAR:

    case R_CAR:
        if((nFromX != nToX) && (nFromY != nToY))//车走直线
        {
            return false;
        }
        if(nFromX == nToX)//竖着走
        {
            if(nFromY > nToY)//往上走
            {
                for(i = nFromY; i < nToY; i--)
                {
                    //目标点和原点之间有棋子
                    if(position[nFromX][i] != NOCHESS)
                    {
                        return false;
                    }
                }
            }
            else//往下走
            {
                for(i = nFromY; i > nToY; i++)
                {
                    if(position[nFromX][i] != NOCHESS)
                    {
                        return false;
                    }
                }
            }
        }
        else //横着走
        {
            if(nFromX > nToX)//往左走
            {
                for(i = nFromX; i < nToX; i--)
                {
                    //目标点与原点之间有棋子
                    if(position[i][nFromY] != NOCHESS)
                    {
                        return false;
                    }
                }
            }
            else//往右走
            {
                for(i = nFromX; i > nToX; i++)
                {
                    //目标与原点之间有棋子
                    if(position[i][nFromY] != NOCHESS)
                    {
                        return false;
                    }
                }
            }
        }
        break;

    case B_CANNON:

    case R_CANNON:
        if((nFromX != nToX) && (nFromY != nToY))//炮走直线
        {
            return false;
        }
        //炮不吃子时  和车实现方法一致，路径上不能有棋子
        if(position[nToX][nToY] == NOCHESS)
        {
            if(nFromX == nToX)//竖着走
            {
                if(nFromY > nToY)//往上走
                {
                    for(i = nFromY; i < nToY; i--)
                    {
                        //目标点和原点之间有棋子
                        if(position[nFromX][i] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
                else//往下走
                {
                    for(i = nFromY; i > nToY; i++)
                    {
                        if(position[nFromX][i] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
            }
            else //横着走
            {
                if(nFromX > nToX)//往左走
                {
                    for(i = nFromX; i < nToX; i--)
                    {
                        //目标点与原点之间有棋子
                        if(position[i][nFromY] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
                else//往右走
                {
                    for(i = nFromX; i > nToX; i++)
                    {
                        //目标与原点之间有棋子
                        if(position[i][nFromY] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        //炮吃子时
        else
        {
            int count = 0;
            if(nFromX == nToX)//竖着走
            {
                if(nFromY > nToY)//往上走
                {
                    for(i = nFromY; i < nToY; i--)
                    {
                        //目标点和原点之间有棋子
                        if(position[nFromX][i] != NOCHESS)
                        {
                            count++;
                        }
                    }
                    //炮和目标棋子之间的棋子个数不是1
                    if(count != 1)
                    {
                        return false;
                    }
                }
                else//往下走
                {
                    for(i = nFromY; i > nToY; i++)
                    {
                        if(position[nFromX][i] != NOCHESS)
                        {
                            count++;
                        }
                    }
                    //炮和目标棋子之间的棋子个数不是1
                    if(count != 1)
                    {
                        return false;
                    }
                }
            }
            else //横着走
            {
                if(nFromX > nToX)//往左走
                {
                    for(i = nFromX; i < nToX; i--)
                    {
                        //目标点与原点之间有棋子
                        if(position[i][nFromY] != NOCHESS)
                        {
                            count++;
                        }
                        //炮和目标棋子之间的棋子个数不是1
                        if(count != 1)
                        {
                            return false;
                        }
                    }
                }
                else//往右走
                {
                    for(i = nFromX; i > nToX; i++)
                    {
                        //目标与原点之间有棋子
                        if(position[i][nFromY] != NOCHESS)
                        {
                            count++;
                        }
                        //炮和目标棋子之间的棋子个数不是1
                        if(count != 1)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        break;

    case B_PAWN://黑兵
        //只能走一步
        if((fabs(nToX - nFromX) + fabs(nToY - nFromY)) > 1)
        {
            return false;
        }
        //过河前不能横走
        if((nFromY < 5) && (nFromX != nToX))
        {
            return false;
        }
        //只能前进
        if(nToY < nFromY)
        {
            return false;
        }
        break;
    case R_PAWN://红卒
        //只能走一步
        if((fabs(nToX - nFromX) + fabs(nToY - nFromY)) > 1)
        {
            return false;
        }
        //过河前不能横走
        if((nFromY > 4) && (nFromX != nToX))
        {
            return false;
        }
        //只能前进
        if(nToY > nFromY)
        {
            return false;
        }
        break;
    default:
        return false;

    }
    return true;
}
//在m_MoveList中插入一个走法
//nFromX是起始位置横坐标
//nFromY是起始位置纵坐标
//nToX是目标位置横坐标
//nToY是目标位置纵坐标
//nPly是此走法所在的层次
int CMoveGenerator::AddMove(int nFromX, int nFromY, int nToX, int nToY, int nPly)
{
    m_MoveList[nPly][m_nMoveCount].From.x = nFromX;
    m_MoveList[nPly][m_nMoveCount].From.y = nFromY;
    m_MoveList[nPly][m_nMoveCount].To.x = nToX;
    m_MoveList[nPly][m_nMoveCount].To.y = nToY;
    m_nMoveCount++;
    return m_nMoveCount;
}
//以上是AddMove

//用以产生局面position中所有可能的走法
//position是包含所有棋子位置信息的二维数组
//nPly指明当前搜索的层数，每层将走法存在不同的位置，以免覆盖
//nSide指明产生哪一方面的走法，true为红方，false是黑方
int CMoveGenerator::CreatepossibleMove(unsigned char position[10][9], int nPly, int nSide)
{
    int i,j;
    int nChessID;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(position[i][j] != NOCHESS)
            {
                nChessID = position[i][j];
                if(!nSide && IsRed(nChessID))
                {
                    continue;//要产生黑棋的走法，跳过红棋
                }
                if(nSide && IsBlack(nChessID))
                {
                    continue;//要产生红棋的走法，跳过黑棋
                }
                switch(nChessID)
                {
                case B_KING://黑将
                case R_KING://红帅
                    Gen_KingMove(position, i, j, nPly);
                    break;

                case B_BISHOP://黑士
                    Gen_BBishopMove(position, i, j, nPly);
                    break;

                case R_BISHOP://红士
                    Gen_RBishopMove(position, i, j, nPly);
                    break;

                case B_ELEPHANT://黑象
                case R_ELEPHANT://红相
                    Gen_ElephantMove(position, i, j, nPly);
                    break;

                case B_HORSE://黑马
                case R_HORSE://红马
                    Gen_HorseMove(position, i, j, nPly);
                    break;

                case B_CAR:
                case R_CAR:
                    Gen_CarMove(position, i, j, nPly);
                    break;

                case B_CANNON://黑炮
                case R_CANNON://红炮
                    Gen_CannonMove(position, i, j, nPly);
                    break;

                case B_PAWN://黑兵
                    Gen_BPawnMove(position, i, j, nPly);
                    break;

                case R_PAWN://红卒
                    Gen_RPawnMove(position, i, j, nPly);
                    break;

                default:
                    break;
                }
            }
        }
    }
    return 0;
}

//产生帅的合法走步
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_KingMove(unsigned char position[10][9], int i, int j, int nPly)
{
    int x, y;
    for(x = 3; x < 6; x++)
    {
        for(y = 0; y < 3; y++)
        {
            if(IsValidMove(position, i, j, x, y))//判断走步是否合法
            {
                AddMove(i, j, x, y, nPly);//将走法插入List
            }
        }
        for(y = 7; y < 10; y++)
        {
            if(IsValidMove(position, i, j, x, y))
            {
                AddMove(i, j, x, y, nPly);//将走法插入List
            }
        }
    }

}
//产生给定棋盘上的给定位置上的红仕的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_RBishopMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    for(x = 3; x < 6; x++)
    {
        for(y = 7; y < 10; y++)
        {
            if(IsValidMove(position, i, j, x, y))
            {
                AddMove(i, j, x, y, nPly);
            }
        }
    }
}
//产生给定棋盘上的给定位置上的黑士的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_BBishopMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    for(x = 3; x < 6; x++)
    {
        for(y = 0; y < 3; y++)
        {
            if(IsValidMove(position, i, j, x, y))
            {
                AddMove(i, j, x, y, nPly);
            }
        }
    }
}
//产生给定棋盘上的给定位置上的相/象的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_ElephantMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    //插入向右下方的有效走法
    x = i + 2;
    y = j + 2;
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    //插入向右上方的有效走法
    x = i + 2;
    y = j - 2;
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //插入向左上方的有效走法
    x = i - 2;
    y = j - 2;
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //插入向左下方的有效走法
    x = i - 2;
    y = j + 2;
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
}
//产生给定棋盘上的给定位置上的马的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_HorseMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    //插入向右下方的有效走法
    x = i + 1;//右一
    y = j + 2;//下二
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i + 2;//右二
    y = j + 1;//下一
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    //插入向右上方的有效走法
    x = i + 1;//右一
    y = j - 2;//上二
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i + 2;//右二
    y = j - 1;//上一
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //插入向左上方的有效走法
    x = i - 1;//左一
    y = j - 2;//上二
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i - 2;//左二
    y = j - 1;//上一
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //插入向左下方的有效走法
    x = i - 1;//左一
    y = j + 2;//下二
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i - 2;//左二
    y = j + 1;//下一
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
}
//产生给定棋盘上的给定位置上的車的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_CarMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y,nChessID;
    nChessID = position[i][j];
    //插入向右的有效走法
    x = i + 1;
    y = j;
    while(x < 9)
    {
        if(position[x][y] != NOCHESS)//从起始位置到棋盘边界有棋子
        {
            if(IsSameSide(nChessID, position[x][y]))//判断该棋子是否和源棋子同色
            {
                break;//同色直接跳出循环
            }
            else
            {
                //不同色将当前位置加入走法,然后退出循环
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //无棋子直接加入走法
            AddMove(i, j, x, y, nPly);
        }
        x++;
    }
    //插入向左的有效走法
    x = i - 1;
    y = j;
    while(x >= 0)
    {
        if(position[x][y] != NOCHESS)//从起始位置到棋盘边界有棋子
        {
            if(IsSameSide(nChessID, position[x][y]))//判断该棋子是否和源棋子同色
            {
                break;//同色直接跳出循环
            }
            else
            {
                //不同色将当前位置加入走法,然后退出循环
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //无棋子直接加入走法
            AddMove(i, j, x, y, nPly);
        }
        x--;
    }
    //插入向上的有效走法
    x = i;
    y = j - 1;
    while(y >= 0)
    {
        if(position[x][y] != NOCHESS)//从起始位置到棋盘边界有棋子
        {
            if(IsSameSide(nChessID, position[x][y]))//判断该棋子是否和源棋子同色
            {
                break;//同色直接跳出循环
            }
            else
            {
                //不同色将当前位置加入走法,然后退出循环
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //无棋子直接加入走法
            AddMove(i, j, x, y, nPly);
        }
        y--;
    }
    //插入向下的有效走法
    x = i;
    y = j + 1;
    while(y < 10)
    {
        if(position[x][y] != NOCHESS)//从起始位置到棋盘边界有棋子
        {
            if(IsSameSide(nChessID, position[x][y]))//判断该棋子是否和源棋子同色
            {
                break;//同色直接跳出循环
            }
            else
            {
                //不同色将当前位置加入走法,然后退出循环
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //无棋子直接加入走法
            AddMove(i, j, x, y, nPly);
        }
        y++;
    }
}
//产生给定棋盘上的给定位置上的红卒的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_RPawnMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y, nChessID;
    nChessID = position[i][j];
    x = i;
    y = j - 1;
    if(i > 4)//没过河
    {
        if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
        {
            AddMove(i, j, x, y, nPly);
        }

    }
    else//已过河
    {
        //插入向上方走法
        x = i;
        y = j - 1;
        if(y >= 0)//位置有效
        {
            if(position[x][y] != NOCHESS)
            {
                //有障碍
                if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //无障碍
                AddMove(i, j, x, y, nPly);
            }
        }

        //插入向左走法
        x = i - 1;
        y = j;
        if(x >= 0)//位置有效
        {
            if(position[x][y] != NOCHESS)
            {
                //有障碍
                if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //无障碍
                AddMove(i, j, x, y, nPly);
            }
        }

        //插入向右走法
        x = i + 1;
        y = j;
        if(x < 9)//位置有效
        {
            if(position[x][y] != NOCHESS)
            {
                //有障碍
                if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //无障碍
                AddMove(i, j, x, y, nPly);
            }
        }
    }
}
//产生给定棋盘上的给定位置上的黑兵的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_BPawnMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y, nChessID;
    nChessID = position[i][j];
    x = i;
    y = j + 1;
    if(i < 5)//没过河
    {
        if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
        {
            AddMove(i, j, x, y, nPly);
        }

    }
    else//已过河
    {
        //插入向上方走法
        x = i;
        y = j + 1;
        if(y < 10)//位置有效
        {
            if(position[x][y] != NOCHESS)
            {
                //有障碍
                if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //无障碍
                AddMove(i, j, x, y, nPly);
            }
        }

        //插入向左走法
        x = i - 1;
        y = j;
        if(x >= 0)//位置有效
        {
            if(position[x][y] != NOCHESS)
            {
                //有障碍
                if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //无障碍
                AddMove(i, j, x, y, nPly);
            }
        }

        //插入向右走法
        x = i + 1;
        y = j;
        if(x < 9)//位置有效
        {
            if(position[x][y] != NOCHESS)
            {
                //有障碍
                if(!IsSameSide(nChessID, position[x][y]))//前方不是同颜色
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //无障碍
                AddMove(i, j, x, y, nPly);
            }
        }
    }
}
//产生给定棋盘上的给定位置上的炮的走法
//i,j是棋子的位置
//nPly表示插入到List的第几层
void CMoveGenerator::Gen_CannonMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y, nChessID;
    nChessID = position[i][j];
    bool flag = false;
    //插入向右走法
    x = i + 1;
    y = j;
    while(x < 9)
    {
        if(flag)
        {
            //已经检测到第一枚棋子,此时应该继续向下检索
            if(position[x][y] != NOCHESS)//检测到第二枚棋子
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //与炮颜色相同
                    break;
                }
                else
                {
                    //与炮颜色不同
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//没棋子
            {
                AddMove(i, j, x, y, nPly);
            }
            else//有棋子
            {
                flag = true;//检测到第一个棋子
            }
        }
        x++;
    }
    //插入向左走法
    x = i - 1;
    y = j;
    while(x >= 0)
    {
        if(flag)
        {
            //已经检测到第一枚棋子,此时应该继续向下检索
            if(position[x][y] != NOCHESS)//检测到第二枚棋子
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //与炮颜色相同
                    break;
                }
                else
                {
                    //与炮颜色不同
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//没棋子
            {
                AddMove(i, j, x, y, nPly);
            }
            else//有棋子
            {
                flag = true;//检测到第一个棋子
            }
        }
        x--;
    }
    //插入向上走法
    x = i;
    y = j - 1;
    while(y >= 0)
    {
        if(flag)
        {
            //已经检测到第一枚棋子,此时应该继续向下检索
            if(position[x][y] != NOCHESS)//检测到第二枚棋子
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //与炮颜色相同
                    break;
                }
                else
                {
                    //与炮颜色不同
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//没棋子
            {
                AddMove(i, j, x, y, nPly);
            }
            else//有棋子
            {
                flag = true;//检测到第一个棋子
            }
        }
        y--;
    }
    //插入向下走法
    x = i;
    y = j + 1;
    while(y < 10)
    {
        if(flag)
        {
            //已经检测到第一枚棋子,此时应该继续向下检索
            if(position[x][y] != NOCHESS)//检测到第二枚棋子
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //与炮颜色相同
                    break;
                }
                else
                {
                    //与炮颜色不同
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//没棋子
            {
                AddMove(i, j, x, y, nPly);
            }
            else//有棋子
            {
                flag = true;//检测到第一个棋子
            }
        }
        y++;
    }

}
