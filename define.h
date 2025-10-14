// define.h  data structure and macros
#ifndef DEFINE_H
#define DEFINE_H

#include <cstdint>

// Cross-platform basic types
typedef uint8_t BYTE;

// Minimal POINT replacement used by evaluation
typedef struct _point {
    int x;
    int y;
} POINT;

#define NOTHING 0  // 没有棋子
#define B_KING 1   // 黑帅
#define B_CAR 2    // 黑車
#define B_HORSE 3  // 黑馬
#define B_CANNON 4 // 黑炮
#define B_BISHOP 5 // 黑士
#define B_ELEPHANT 6 // 黑象
#define B_PAWN 7   // 黑兵
#define B_BEGIN B_KING
#define B_END B_PAWN

#define R_KING 8   // 红将
#define R_CAR 9    // 红車
#define R_HORSE 10 // 红馬
#define R_CANNON 11 // 红炮
#define R_BISHOP 12 // 红仕
#define R_ELEPHANT 13 // 红相
#define R_PAWN 14  // 红卒
#define R_BEGIN R_KING
#define R_END R_PAWN

// 判断一个棋子是不是黑色
#define IsBlack(x) (x >= B_BEGIN && x <= B_END)
// 判断一个棋子是不是红色
#define IsRed(x) (x >= R_BEGIN && x <= R_END)
// 判断两个棋子是不是同色
#define IsSameSide(x, y) ((IsBlack(x) && IsBlack(y)) || (IsRed(x) && IsRed(y)))

// 定义一个棋子位置的结构
typedef struct _chessmanposition
{
    BYTE x;
    BYTE y;
} CHESSMANPOS;

// 一个走法的结构
typedef struct _chessmove
{
    short ChessID;          // 标明是什么棋子
    CHESSMANPOS From;       // 起始位置
    CHESSMANPOS To;         // 走到的位置
    int Score;              // 值
} CHESSMOVE;

#endif // DEFINE_H
