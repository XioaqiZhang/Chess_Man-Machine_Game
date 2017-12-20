#ifndef DEFINE_H
#define DEFINE_H

#define BYTE unsigned char

#define NOCHESS     0  //û������
#define B_KING      1  //�ڽ�
#define B_CAR       2  //�ڳ�
#define B_HORSE     3  //����
#define B_CANNON    4  //����
#define B_BISHOP    5  //��ʿ
#define B_ELEPHANT  6  //����
#define B_PAWN      7  //����
#define B_BEGIN     B_KING
#define B_END       B_PAWN

#define R_KING      8  //�콫
#define R_CAR       9  //�쳵
#define R_HORSE     10 //����
#define R_CANNON    11 //����
#define R_BISHOP    12 //��ʿ
#define R_ELEPHANT  13 //����
#define R_PAWN      14 //����
#define R_BEGIN     R_KING
#define R_END       R_PAWN

#define IsBlack(x)  (x >= B_BEGIN && x <= B_END) //�ж�һ�������ǲ��Ǻ�ɫ
#define IsRed(x)    ((x >= R_BEGIN) && (x <= R_END))
//�ж����������ǲ���ͬɫ
#define IsSameSide(x,y) ((IsBlack(x) && IsBlack(y)) || (IsRed(x) && IsRed(y)) )
//true
//����һ������λ�õĽṹ
typedef struct chessmanposition
{
    BYTE x;
    BYTE y;
}CHESSMANPOS;

//һ���߷��Ľṹ
typedef struct _chessmove
{
    short       ChessID;
    CHESSMANPOS From;
    CHESSMANPOS To;
    int         Score;

}CHESSMOVE;


#endif // DEFINE_H
