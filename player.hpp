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
    Move *getBestMoveHeuristic();
    Move *getBestMoveMiniMax(Board * board, int rec_time, int rec_depth);
    vector<Move> getMoves(Board * board);
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
