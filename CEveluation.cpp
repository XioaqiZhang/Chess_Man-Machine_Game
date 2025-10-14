// Simple evaluation engine implementation
#include "CEveluation.h"
#include <cstring>

CEveluation::CEveluation()
{
	// Initialize base values (index by piece id 0..14)
	for (int i = 0; i < 15; ++i)
	{
		m_BaseValue[i] = 0;
		m_FlexValue[i] = 0;
	}
	m_BaseValue[B_PAWN] = BASEVALUE_PAWN;
	m_BaseValue[B_BISHOP] = BASEVALUE_BISHOP;
	m_BaseValue[B_ELEPHANT] = BASEVALUE_ELEPHANT;
	m_BaseValue[B_HORSE] = BASEVALUE_HORSE;
	m_BaseValue[B_CAR] = BASEVALUE_CAR;
	m_BaseValue[B_CANNON] = BASEVALUE_CANON;
	m_BaseValue[B_KING] = BASEVALUE_KING;
	m_BaseValue[R_PAWN] = BASEVALUE_PAWN;
	m_BaseValue[R_BISHOP] = BASEVALUE_BISHOP;
	m_BaseValue[R_ELEPHANT] = BASEVALUE_ELEPHANT;
	m_BaseValue[R_HORSE] = BASEVALUE_HORSE;
	m_BaseValue[R_CAR] = BASEVALUE_CAR;
	m_BaseValue[R_CANNON] = BASEVALUE_CANON;
	m_BaseValue[R_KING] = BASEVALUE_KING;
}

CEveluation::~CEveluation() = default;

int CEveluation::Evaluate(BYTE position[10][9], bool blsRedTurn)
{
	// Very basic material evaluation: sum red - black
	int red = 0, black = 0;
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 9; ++x)
		{
			BYTE id = position[y][x];
			if (id == NOTHING) continue;
			if (IsRed(id)) red += m_BaseValue[id];
			else if (IsBlack(id)) black += m_BaseValue[id];
		}
	}
	int score = red - black;
	// From the perspective of the side to move
	return blsRedTurn ? score : -score;
}

int CEveluation::GetRelatePiece(BYTE position[10][9], int i, int j)
{
	// Placeholder: not used by simple evaluation
	(void)position; (void)i; (void)j;
	return 0;
}

bool CEveluation::CanTouch(BYTE position[10][9], int nFromX, int nFromY, int nToX, int nToY)
{
	// Placeholder: rely on move generator elsewhere
	(void)position; (void)nFromX; (void)nFromY; (void)nToX; (void)nToY;
	return false;
}

void CEveluation::AddPoint(int x, int y)
{
	// Placeholder to satisfy interface
	(void)x; (void)y;
}
