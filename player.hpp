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
    Move *MiniMax(Board * myboard, int depth);
    int getBestMoveMiniMax(Board * board, int depth, bool turn);
    vector<Move> getMoves(Board * board, Side side);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
