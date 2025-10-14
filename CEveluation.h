#ifndef CEVELUATION_H
#define CEVELUATION_H

#include "define.h"

// 定义每种棋子的基本价值
// 兵100，士250，相250，马350，车500，炮350，将10000
#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 250
#define BASEVALUE_ELEPHANT 250
#define BASEVALUE_HORSE 350
#define BASEVALUE_CAR 500
#define BASEVALUE_CANON 350
#define BASEVALUE_KING 10000

// 定义棋子的灵活性
// 每多一个可走位置，增加一定的分值
// 兵15，士1，相1，马12，车6，炮6，将0
#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_BISHOP 1
#define FLEXIBILITY_ELEPHANT 1
#define FLEXIBILITY_HORSE 12
#define FLEXIBILITY_CAR 6
#define FLEXIBILITY_CANON 6
#define FLEXIBILITY_KING 0

class CEveluation
{
public:
    CEveluation();
    virtual ~CEveluation();
    // 估值函数，对传入的棋盘打分，blsRedTurn为真时表示红方走
    virtual int Evaluate(BYTE position[10][9], bool blsRedTurn);
protected:
    // 列举与指定位置的棋子相关的棋子
    int GetRelatePiece(BYTE position[10][9], int i, int j);
    // 判断位置 From 的棋子是否能走到位置 To
    bool CanTouch(BYTE position[10][9], int nFromX, int nFromY, int nToX, int nToY);
    // 将一个位置加入相关位置队列
    void AddPoint(int x, int y);
    // 存放棋子基本价值的数组
    int m_BaseValue[15];
    // 存放棋子灵活性的数组
    int m_FlexValue[15];
    // 存放每一位置被威胁的程度
    int m_AttackPos[10][9];
    // 存放每一位置被保护的程度
    int m_GuardPos[10][9];
    // 存放每一位置的灵活性
    int m_FlexibilityPos[10][9];
    // 存放每一位置上棋子的总价值
    int m_chessValue[10][9];
    // 记录棋子的相关位置个数
    int nPosCount;
    // 记录一个棋子相关位置的数组
    POINT RelatePos[20];

};

#endif // CEVELUATION_H
