#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include "define.h"
#include "CMoveGenerator.h"
#include "CNegaMaxEngine.h"

// Simple game state wrapper around core engine
class GameState {
public:
    GameState();

    // Initialize to standard Xiangqi starting position
    void reset();

    // Control start state
    void start() { m_started = true; }
    void stop() { m_started = false; }
    bool started() const { return m_started; }

    // Get current board
    const BYTE (&board() const)[10][9] { return m_board; }

    // Try to make a move from (fx,fy) to (tx,ty). Returns true if applied.
    bool tryMove(int fx, int fy, int tx, int ty);

    // Is red to move?
    bool redTurn() const { return m_redTurn; }

    // Let AI make a move for current side
    void aiMove();

    // Check if game is over: 1 = Red wins, -1 = Black wins, 0 = ongoing
    int checkGameOver() const;

private:
    BYTE m_board[10][9];
    bool m_redTurn; // true = red to move, false = black
    bool m_started{false};

    CMoveGenerator m_gen;
    CEveluation m_eval;
    CNegaMaxEngine m_engine;
};

#endif // GAMESTATE_H
