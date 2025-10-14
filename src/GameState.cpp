#include "GameState.h"
#include <cstring>

GameState::GameState() : m_redTurn(true) {
    reset();
    m_engine.SetMoveGenerator(&m_gen);
    m_engine.SetEvaluator(&m_eval);
    m_engine.SetSearchDepth(4);
}

void GameState::reset() {
    // Clear
    for (int y = 0; y < 10; ++y)
        for (int x = 0; x < 9; ++x)
            m_board[y][x] = NOTHING;

    // Black back rank (top)
    m_board[0][0] = m_board[0][8] = B_CAR;
    m_board[0][1] = m_board[0][7] = B_HORSE;
    m_board[0][2] = m_board[0][6] = B_ELEPHANT;
    m_board[0][3] = m_board[0][5] = B_BISHOP;
    m_board[0][4] = B_KING;
    m_board[2][1] = m_board[2][7] = B_CANNON;
    for (int x = 0; x < 9; x += 2) m_board[3][x] = B_PAWN;

    // Red back rank (bottom)
    m_board[9][0] = m_board[9][8] = R_CAR;
    m_board[9][1] = m_board[9][7] = R_HORSE;
    m_board[9][2] = m_board[9][6] = R_ELEPHANT;
    m_board[9][3] = m_board[9][5] = R_BISHOP;
    m_board[9][4] = R_KING;
    m_board[7][1] = m_board[7][7] = R_CANNON;
    for (int x = 0; x < 9; x += 2) m_board[6][x] = R_PAWN;

    m_redTurn = true;
}

bool GameState::tryMove(int fx, int fy, int tx, int ty) {
    if (fx < 0 || fx >= 9 || tx < 0 || tx >= 9 || fy < 0 || fy >= 10 || ty < 0 || ty >= 10)
        return false;
    BYTE id = m_board[fy][fx];
    if (id == NOTHING) return false;
    if (m_redTurn && !IsRed(id)) return false;
    if (!m_redTurn && !IsBlack(id)) return false;
    if (!CMoveGenerator::IsValidMove(m_board, fx, fy, tx, ty)) return false;

    BYTE captured = m_board[ty][tx];
    m_board[ty][tx] = id;
    m_board[fy][fx] = NOTHING;

    m_redTurn = !m_redTurn;
    return true;
}

void GameState::aiMove() {
    // Let engine play for current side: engine assumes side is ((maxDepth-depth)%2)
    // We'll call it once and it will modify m_board in place
    m_engine.SearchAGoodMove(m_board);
    m_redTurn = !m_redTurn;
}

int GameState::checkGameOver() const {
    bool redLive = false, blackLive = false;
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 9; ++x) {
            if (m_board[y][x] == R_KING) redLive = true;
            if (m_board[y][x] == B_KING) blackLive = true;
        }
    }
    if (!redLive && !blackLive) return 0; // invalid, but treat as ongoing
    if (!redLive) return -1; // black wins
    if (!blackLive) return 1; // red wins
    return 0;
}
