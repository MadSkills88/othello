/*
 * Team Name: freefood
 * Team members: Anthony Bao, Sam Owen
 */

// Zach said I could put "lol". Lol.

#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = new Board();
    myside = side;
    if (myside == BLACK) {
       oppside = WHITE;
    }
    else {
       oppside = BLACK;
    }

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board->doMove(opponentsMove, oppside);
    if (!board->hasMoves(myside)) {
        return nullptr;
    }
    Move *best = getBestMoveMiniMax();
    // std::cerr << best->getX() << ", " << best->getY() << std::endl;
    board->doMove(best, myside);
    return best;

}

Move *Player::getBestMoveHeuristic()   {
    Move *best;
    int score = -65*3;
    int move_index;
    std::vector<Move> moves = getMoves(board);
    // std::cerr << "number of potential moves: " << moves.size() << std::endl;
    for (unsigned int i = 0; i < moves.size(); i++) {
        Board * newboard = board->copy();
        // std::cerr << "potential move: " << moves[i].getX() << ", " << moves[i].getY() << std::endl;
        newboard->doMove(&moves[i], myside);
        int newscore = newboard->count(myside) - newboard->count(oppside);
        // corner
        if ((moves[i].getX() == 0 || moves[i].getX() == 7) && ((moves[i].getY() == 0 || moves[i].getY() == 7)))   {
            newscore *= 3;
        }
        // adjacent to corners
        if (moves.size() > 1)   {
            std::vector<Move> adjacent_corner = {Move(1, 0), Move(0, 1), Move(1, 1),
              Move(6, 0), Move(6, 1), Move(7, 1), Move(0, 6), Move(1, 6), Move(1, 7),
              Move(6, 7), Move(6, 6), Move(7, 6)};
            for (unsigned int j = 0; j < adjacent_corner.size(); ++j)   {
                if (moves[i].getX() == adjacent_corner[j].getX() && moves[i].getY() == adjacent_corner[j].getY())   {
                    newscore *= -3;
                }
            }
        }
        // std::cerr << "score for this move: " << newscore << std::endl;
        // std::cerr << "number on myside: " << newboard->count(myside) << std::endl;
        // std::cerr << "number on oppside: " << newboard->count(oppside) << std::endl;
        if (newscore > score) {
            move_index = i;
            score = newscore;
        }
  }
  // std::cerr << "move index: " << move_index << std::endl;
  best = &moves[move_index];
  best = new Move(best->getX(), best->getY());
  return best;
}

Move *Player::getBestMoveMiniMax(Board * board, int rec_time, int rec_depth) {
    rec_time -= 1;
    rec_depth += 1;
    if (rec_depth == 0)   {
        return getBestMoveHeuristic();
    }
    Move *best;
    int score = -65*3;
    int move_index;
    std::vector<Move> moves = getMoves(board);

    // std::cerr << "number of potential moves: " << moves.size() << std::endl;
    for (unsigned int i = 0; i < moves.size(); i++) {
        Board * newboard = board->copy();
        // std::cerr << "potential move: " << moves[i].getX() << ", " << moves[i].getY() << std::endl;
        newboard->doMove(&moves[i], myside);
        int newscore = newboard->count(myside) - newboard->count(oppside);

        if (newscore > score) {
            move_index = i;
            score = newscore;
        }
    }
    // std::cerr << "move index: " << move_index << std::endl;
    best = &moves[move_index];
    best = new Move(best->getX(), best->getY());
    return best;
}

std::vector<Move> Player::getMoves(Board * board) {
    // moves.clear();
    std::vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (board->checkMove(&move, myside)) {
                moves.push_back(move);
            }
            // moves.push_back(move);
        }
    }
    return moves;
}
