#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include "vector"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    Board * board;
    Side oppside;
    Side myside;
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *getBestMoveHeuristic(Board * myboard, Side side);
    int getBestScoreHeuristic(Board * myboard, Move * move, Side side);
    Move *getBestMoveMiniMax(Board * myboard, int depth);
    int getMiniMaxScore(Board * myboard, int depth, bool turn);
    vector<Move*> getMoves(Board * myboard, Side side);
    int mobilitycalc(Board * myboard, Side side);
    int sidestability(Board * myboard, Side side, Move * move);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
