#include "CMoveGenerator.h"
#include "define.h"
#include "math.h"
//���캯��
CMoveGenerator::CMoveGenerator()
{
}
//��������
CMoveGenerator::~CMoveGenerator()
{
}

//�жϾ���position�ϣ���From��To���߷��Ƿ�Ϸ�
//����ǺϷ��߷�������TRUE�����򷵻�FALSE
bool CMoveGenerator::IsValidMove(BYTE position[10][9],
                                 int nFromX, int nFromY, int nToX, int nToY)
{
    int nMoveChessID,nTargetID;
    int i,j;
    if((nFromX == nToX)&&(nFromY == nToY))
    {
        return false;//Ŀ����Դ��ͬ���Ƿ�
    }
    nMoveChessID = position[nFromX][nFromY];
    nTargetID = position[nToX][nToY];
    if(IsSameSide(nMoveChessID, nTargetID))
    {
        return false;//���Լ����壬�Ƿ�
    }

    switch(nMoveChessID)
    {
    case B_KING://�ڽ�
        if(nTargetID == R_KING)//�ж��Ͻ��Ƿ����
        {
            if(nFromX != nToX)//�����겻���
            {
                return false;  //��������ͬһ��
            }
            for(i = nFromY + 1; i < nToY; i++)
            {
                if(position[i][nFromY] != NOCHESS)//�м�û������
                {
                    return false;
                }
            }
        }
        else
        {
            if((nToX > 5) || (nToX < 3) || (nToY > 2))//Ŀ����ڽ���֮��
            {
                return false;
            }
            if((fabs(nFromX - nToX) + fabs(nFromY - nToY)) > 1)//��/˧�߳���һ��
            {
                return false;
            }
        }
        break;
    case R_KING://��˧
        if(nTargetID == B_KING)//�ж��Ͻ��Ƿ����
        {
            if(nFromX != nToX)//�����겻���
            {
                return false;//��������ͬһ��
            }
            for(i = nFromY - 1; i > nToY; i--)
            {
                if(position[i][nFromY] != NOCHESS)//֮��������
                {
                    return false;
                }
            }
        }
        else
        {
            if((nToY > 5) || (nToY < 3) || (nToX < 7))//Ŀ����ڽ���֮��
            {
                return false;
            }
            if(fabs(nFromX - nToX) + fabs(nFromY - nToY) > 1)//���߳���1��
            {
                return false;
            }
        }
        break;
    case B_BISHOP://��ʿ
        if((nToX < 3) || (nToX > 5) || (nToY > 2))//Ŀ����ڽ�����
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 1) || (fabs(nToY - nFromY) != 1))//ʿ��б��
        {
            return false;
        }
        break;
    case R_BISHOP://��ʿ
        if((nToX < 3) || (nToX > 5) || (nToY < 7))//Ŀ����ڽ�����
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 1) || (fabs(nToY - nFromY) != 1))//ʿ��б��
        {
            return false;
        }
        break;
    case B_ELEPHANT://����
        if(nToY > 4)//���ܹ���
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 2) || (fabs(nToY - nFromY) != 2))//��������
        {
            return false;
        }
        if(position[(nFromX - nToX)/2][(nFromY - nToY)/2] != NOCHESS)//���۱���
        {
            return false;
        }
        break;
    case R_ELEPHANT://����
        if(nToY < 5)//�಻�ܹ���
        {
            return false;
        }
        if((fabs(nToX - nFromX) != 2) || (fabs(nToY - nFromY) != 2))//��������
        {
            return false;
        }
        if(position[(nFromX - nToX)/2][(nFromY - nToY)/2] != NOCHESS)//���۱���
        {
            return false;
        }
        break;
    case B_HORSE://����

    case R_HORSE://����
        //��������
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
        if(position[i][j] != NOCHESS)//������
        {
            return false;
        }
        break;
    case B_CAR:

    case R_CAR:
        if((nFromX != nToX) && (nFromY != nToY))//����ֱ��
        {
            return false;
        }
        if(nFromX == nToX)//������
        {
            if(nFromY > nToY)//������
            {
                for(i = nFromY; i < nToY; i--)
                {
                    //Ŀ����ԭ��֮��������
                    if(position[nFromX][i] != NOCHESS)
                    {
                        return false;
                    }
                }
            }
            else//������
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
        else //������
        {
            if(nFromX > nToX)//������
            {
                for(i = nFromX; i < nToX; i--)
                {
                    //Ŀ�����ԭ��֮��������
                    if(position[i][nFromY] != NOCHESS)
                    {
                        return false;
                    }
                }
            }
            else//������
            {
                for(i = nFromX; i > nToX; i++)
                {
                    //Ŀ����ԭ��֮��������
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
        if((nFromX != nToX) && (nFromY != nToY))//����ֱ��
        {
            return false;
        }
        //�ڲ�����ʱ  �ͳ�ʵ�ַ���һ�£�·���ϲ���������
        if(position[nToX][nToY] == NOCHESS)
        {
            if(nFromX == nToX)//������
            {
                if(nFromY > nToY)//������
                {
                    for(i = nFromY; i < nToY; i--)
                    {
                        //Ŀ����ԭ��֮��������
                        if(position[nFromX][i] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
                else//������
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
            else //������
            {
                if(nFromX > nToX)//������
                {
                    for(i = nFromX; i < nToX; i--)
                    {
                        //Ŀ�����ԭ��֮��������
                        if(position[i][nFromY] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
                else//������
                {
                    for(i = nFromX; i > nToX; i++)
                    {
                        //Ŀ����ԭ��֮��������
                        if(position[i][nFromY] != NOCHESS)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        //�ڳ���ʱ
        else
        {
            int count = 0;
            if(nFromX == nToX)//������
            {
                if(nFromY > nToY)//������
                {
                    for(i = nFromY; i < nToY; i--)
                    {
                        //Ŀ����ԭ��֮��������
                        if(position[nFromX][i] != NOCHESS)
                        {
                            count++;
                        }
                    }
                    //�ں�Ŀ������֮������Ӹ�������1
                    if(count != 1)
                    {
                        return false;
                    }
                }
                else//������
                {
                    for(i = nFromY; i > nToY; i++)
                    {
                        if(position[nFromX][i] != NOCHESS)
                        {
                            count++;
                        }
                    }
                    //�ں�Ŀ������֮������Ӹ�������1
                    if(count != 1)
                    {
                        return false;
                    }
                }
            }
            else //������
            {
                if(nFromX > nToX)//������
                {
                    for(i = nFromX; i < nToX; i--)
                    {
                        //Ŀ�����ԭ��֮��������
                        if(position[i][nFromY] != NOCHESS)
                        {
                            count++;
                        }
                        //�ں�Ŀ������֮������Ӹ�������1
                        if(count != 1)
                        {
                            return false;
                        }
                    }
                }
                else//������
                {
                    for(i = nFromX; i > nToX; i++)
                    {
                        //Ŀ����ԭ��֮��������
                        if(position[i][nFromY] != NOCHESS)
                        {
                            count++;
                        }
                        //�ں�Ŀ������֮������Ӹ�������1
                        if(count != 1)
                        {
                            return false;
                        }
                    }
                }
            }
        }
        break;

    case B_PAWN://�ڱ�
        //ֻ����һ��
        if((fabs(nToX - nFromX) + fabs(nToY - nFromY)) > 1)
        {
            return false;
        }
        //����ǰ���ܺ���
        if((nFromY < 5) && (nFromX != nToX))
        {
            return false;
        }
        //ֻ��ǰ��
        if(nToY < nFromY)
        {
            return false;
        }
        break;
    case R_PAWN://����
        //ֻ����һ��
        if((fabs(nToX - nFromX) + fabs(nToY - nFromY)) > 1)
        {
            return false;
        }
        //����ǰ���ܺ���
        if((nFromY > 4) && (nFromX != nToX))
        {
            return false;
        }
        //ֻ��ǰ��
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
//��m_MoveList�в���һ���߷�
//nFromX����ʼλ�ú�����
//nFromY����ʼλ��������
//nToX��Ŀ��λ�ú�����
//nToY��Ŀ��λ��������
//nPly�Ǵ��߷����ڵĲ��
int CMoveGenerator::AddMove(int nFromX, int nFromY, int nToX, int nToY, int nPly)
{
    m_MoveList[nPly][m_nMoveCount].From.x = nFromX;
    m_MoveList[nPly][m_nMoveCount].From.y = nFromY;
    m_MoveList[nPly][m_nMoveCount].To.x = nToX;
    m_MoveList[nPly][m_nMoveCount].To.y = nToY;
    m_nMoveCount++;
    return m_nMoveCount;
}
//������AddMove

//���Բ�������position�����п��ܵ��߷�
//position�ǰ�����������λ����Ϣ�Ķ�ά����
//nPlyָ����ǰ�����Ĳ�����ÿ�㽫�߷����ڲ�ͬ��λ�ã����⸲��
//nSideָ��������һ������߷���trueΪ�췽��false�Ǻڷ�
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
                    continue;//Ҫ����������߷�����������
                }
                if(nSide && IsBlack(nChessID))
                {
                    continue;//Ҫ����������߷�����������
                }
                switch(nChessID)
                {
                case B_KING://�ڽ�
                case R_KING://��˧
                    Gen_KingMove(position, i, j, nPly);
                    break;

                case B_BISHOP://��ʿ
                    Gen_BBishopMove(position, i, j, nPly);
                    break;

                case R_BISHOP://��ʿ
                    Gen_RBishopMove(position, i, j, nPly);
                    break;

                case B_ELEPHANT://����
                case R_ELEPHANT://����
                    Gen_ElephantMove(position, i, j, nPly);
                    break;

                case B_HORSE://����
                case R_HORSE://����
                    Gen_HorseMove(position, i, j, nPly);
                    break;

                case B_CAR:
                case R_CAR:
                    Gen_CarMove(position, i, j, nPly);
                    break;

                case B_CANNON://����
                case R_CANNON://����
                    Gen_CannonMove(position, i, j, nPly);
                    break;

                case B_PAWN://�ڱ�
                    Gen_BPawnMove(position, i, j, nPly);
                    break;

                case R_PAWN://����
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

//����˧�ĺϷ��߲�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_KingMove(unsigned char position[10][9], int i, int j, int nPly)
{
    int x, y;
    for(x = 3; x < 6; x++)
    {
        for(y = 0; y < 3; y++)
        {
            if(IsValidMove(position, i, j, x, y))//�ж��߲��Ƿ�Ϸ�
            {
                AddMove(i, j, x, y, nPly);//���߷�����List
            }
        }
        for(y = 7; y < 10; y++)
        {
            if(IsValidMove(position, i, j, x, y))
            {
                AddMove(i, j, x, y, nPly);//���߷�����List
            }
        }
    }

}
//�������������ϵĸ���λ���ϵĺ��˵��߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
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
//�������������ϵĸ���λ���ϵĺ�ʿ���߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
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
//�������������ϵĸ���λ���ϵ���/����߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_ElephantMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    //���������·�����Ч�߷�
    x = i + 2;
    y = j + 2;
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    //���������Ϸ�����Ч�߷�
    x = i + 2;
    y = j - 2;
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //���������Ϸ�����Ч�߷�
    x = i - 2;
    y = j - 2;
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //���������·�����Ч�߷�
    x = i - 2;
    y = j + 2;
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
}
//�������������ϵĸ���λ���ϵ�����߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_HorseMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y;
    //���������·�����Ч�߷�
    x = i + 1;//��һ
    y = j + 2;//�¶�
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i + 2;//�Ҷ�
    y = j + 1;//��һ
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    //���������Ϸ�����Ч�߷�
    x = i + 1;//��һ
    y = j - 2;//�϶�
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i + 2;//�Ҷ�
    y = j - 1;//��һ
    if(IsValidMove(position, i, j, x, y) && (x < 9) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //���������Ϸ�����Ч�߷�
    x = i - 1;//��һ
    y = j - 2;//�϶�
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i - 2;//���
    y = j - 1;//��һ
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y >= 0))
    {
        AddMove(i, j, x, y, nPly);
    }
    //���������·�����Ч�߷�
    x = i - 1;//��һ
    y = j + 2;//�¶�
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
    x = i - 2;//���
    y = j + 1;//��һ
    if(IsValidMove(position, i, j, x, y) && (x >= 0) && (y < 10))
    {
        AddMove(i, j, x, y, nPly);
    }
}
//�������������ϵĸ���λ���ϵ�܇���߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_CarMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y,nChessID;
    nChessID = position[i][j];
    //�������ҵ���Ч�߷�
    x = i + 1;
    y = j;
    while(x < 9)
    {
        if(position[x][y] != NOCHESS)//����ʼλ�õ����̱߽�������
        {
            if(IsSameSide(nChessID, position[x][y]))//�жϸ������Ƿ��Դ����ͬɫ
            {
                break;//ͬɫֱ������ѭ��
            }
            else
            {
                //��ͬɫ����ǰλ�ü����߷�,Ȼ���˳�ѭ��
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //������ֱ�Ӽ����߷�
            AddMove(i, j, x, y, nPly);
        }
        x++;
    }
    //�����������Ч�߷�
    x = i - 1;
    y = j;
    while(x >= 0)
    {
        if(position[x][y] != NOCHESS)//����ʼλ�õ����̱߽�������
        {
            if(IsSameSide(nChessID, position[x][y]))//�жϸ������Ƿ��Դ����ͬɫ
            {
                break;//ͬɫֱ������ѭ��
            }
            else
            {
                //��ͬɫ����ǰλ�ü����߷�,Ȼ���˳�ѭ��
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //������ֱ�Ӽ����߷�
            AddMove(i, j, x, y, nPly);
        }
        x--;
    }
    //�������ϵ���Ч�߷�
    x = i;
    y = j - 1;
    while(y >= 0)
    {
        if(position[x][y] != NOCHESS)//����ʼλ�õ����̱߽�������
        {
            if(IsSameSide(nChessID, position[x][y]))//�жϸ������Ƿ��Դ����ͬɫ
            {
                break;//ͬɫֱ������ѭ��
            }
            else
            {
                //��ͬɫ����ǰλ�ü����߷�,Ȼ���˳�ѭ��
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //������ֱ�Ӽ����߷�
            AddMove(i, j, x, y, nPly);
        }
        y--;
    }
    //�������µ���Ч�߷�
    x = i;
    y = j + 1;
    while(y < 10)
    {
        if(position[x][y] != NOCHESS)//����ʼλ�õ����̱߽�������
        {
            if(IsSameSide(nChessID, position[x][y]))//�жϸ������Ƿ��Դ����ͬɫ
            {
                break;//ͬɫֱ������ѭ��
            }
            else
            {
                //��ͬɫ����ǰλ�ü����߷�,Ȼ���˳�ѭ��
                AddMove(i, j, x, y, nPly);
                break;
            }
        }
        else
        {
            //������ֱ�Ӽ����߷�
            AddMove(i, j, x, y, nPly);
        }
        y++;
    }
}
//�������������ϵĸ���λ���ϵĺ�����߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_RPawnMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y, nChessID;
    nChessID = position[i][j];
    x = i;
    y = j - 1;
    if(i > 4)//û����
    {
        if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
        {
            AddMove(i, j, x, y, nPly);
        }

    }
    else//�ѹ���
    {
        //�������Ϸ��߷�
        x = i;
        y = j - 1;
        if(y >= 0)//λ����Ч
        {
            if(position[x][y] != NOCHESS)
            {
                //���ϰ�
                if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //���ϰ�
                AddMove(i, j, x, y, nPly);
            }
        }

        //���������߷�
        x = i - 1;
        y = j;
        if(x >= 0)//λ����Ч
        {
            if(position[x][y] != NOCHESS)
            {
                //���ϰ�
                if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //���ϰ�
                AddMove(i, j, x, y, nPly);
            }
        }

        //���������߷�
        x = i + 1;
        y = j;
        if(x < 9)//λ����Ч
        {
            if(position[x][y] != NOCHESS)
            {
                //���ϰ�
                if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //���ϰ�
                AddMove(i, j, x, y, nPly);
            }
        }
    }
}
//�������������ϵĸ���λ���ϵĺڱ����߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_BPawnMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y, nChessID;
    nChessID = position[i][j];
    x = i;
    y = j + 1;
    if(i < 5)//û����
    {
        if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
        {
            AddMove(i, j, x, y, nPly);
        }

    }
    else//�ѹ���
    {
        //�������Ϸ��߷�
        x = i;
        y = j + 1;
        if(y < 10)//λ����Ч
        {
            if(position[x][y] != NOCHESS)
            {
                //���ϰ�
                if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //���ϰ�
                AddMove(i, j, x, y, nPly);
            }
        }

        //���������߷�
        x = i - 1;
        y = j;
        if(x >= 0)//λ����Ч
        {
            if(position[x][y] != NOCHESS)
            {
                //���ϰ�
                if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //���ϰ�
                AddMove(i, j, x, y, nPly);
            }
        }

        //���������߷�
        x = i + 1;
        y = j;
        if(x < 9)//λ����Ч
        {
            if(position[x][y] != NOCHESS)
            {
                //���ϰ�
                if(!IsSameSide(nChessID, position[x][y]))//ǰ������ͬ��ɫ
                {
                    AddMove(i, j, x, y, nPly);
                }
            }
            else
            {
                //���ϰ�
                AddMove(i, j, x, y, nPly);
            }
        }
    }
}
//�������������ϵĸ���λ���ϵ��ڵ��߷�
//i,j�����ӵ�λ��
//nPly��ʾ���뵽List�ĵڼ���
void CMoveGenerator::Gen_CannonMove(BYTE position[10][9], int i, int j, int nPly)
{
    int x, y, nChessID;
    nChessID = position[i][j];
    bool flag = false;
    //���������߷�
    x = i + 1;
    y = j;
    while(x < 9)
    {
        if(flag)
        {
            //�Ѿ���⵽��һö����,��ʱӦ�ü������¼���
            if(position[x][y] != NOCHESS)//��⵽�ڶ�ö����
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //������ɫ��ͬ
                    break;
                }
                else
                {
                    //������ɫ��ͬ
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//û����
            {
                AddMove(i, j, x, y, nPly);
            }
            else//������
            {
                flag = true;//��⵽��һ������
            }
        }
        x++;
    }
    //���������߷�
    x = i - 1;
    y = j;
    while(x >= 0)
    {
        if(flag)
        {
            //�Ѿ���⵽��һö����,��ʱӦ�ü������¼���
            if(position[x][y] != NOCHESS)//��⵽�ڶ�ö����
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //������ɫ��ͬ
                    break;
                }
                else
                {
                    //������ɫ��ͬ
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//û����
            {
                AddMove(i, j, x, y, nPly);
            }
            else//������
            {
                flag = true;//��⵽��һ������
            }
        }
        x--;
    }
    //���������߷�
    x = i;
    y = j - 1;
    while(y >= 0)
    {
        if(flag)
        {
            //�Ѿ���⵽��һö����,��ʱӦ�ü������¼���
            if(position[x][y] != NOCHESS)//��⵽�ڶ�ö����
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //������ɫ��ͬ
                    break;
                }
                else
                {
                    //������ɫ��ͬ
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//û����
            {
                AddMove(i, j, x, y, nPly);
            }
            else//������
            {
                flag = true;//��⵽��һ������
            }
        }
        y--;
    }
    //���������߷�
    x = i;
    y = j + 1;
    while(y < 10)
    {
        if(flag)
        {
            //�Ѿ���⵽��һö����,��ʱӦ�ü������¼���
            if(position[x][y] != NOCHESS)//��⵽�ڶ�ö����
            {
                if(IsSameSide(nChessID, position[x][y]))
                {
                    //������ɫ��ͬ
                    break;
                }
                else
                {
                    //������ɫ��ͬ
                    AddMove(i, j, x, y, nPly);
                    break;
                }
            }
        }
        else
        {
            if(position[x][y] == NOCHESS)//û����
            {
                AddMove(i, j, x, y, nPly);
            }
            else//������
            {
                flag = true;//��⵽��һ������
            }
        }
        y++;
    }

}
