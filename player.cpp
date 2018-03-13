/*
 * Team Name: freefood
 * Team members: Anthony Bao, Sam Owen
 */

// Zach said I could put "lol". Lol.

#include "player.hpp"
#include <climits>
#include <stdlib.h>

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
    // To test Heuristic set: Move *best = getBestMoveHeuristic(Board, myside);
    // To test MiniMax set: Move *best = getBestMoveMiniMax(Board, 3)
    Move *best = getBestMoveMiniMax(board, 4);
    // Move *best = getBestMoveHeuristic(board, myside);
    // std::cerr << best->getX() << ", " << best->getY() << std::endl;
    board->doMove(best, myside);
    return best;

}

Move *Player::getBestMoveHeuristic(Board * myboard, Side side)   {
    Move *best;
    int score = INT_MIN;
    int move_index;
    std::vector<Move*> moves = getMoves(myboard, side);
    // std::cerr << "number of potential moves: " << moves.size() << std::endl;
    for (unsigned int i = 0; i < moves.size(); i++) {
        int newscore = getBestScoreHeuristic(myboard, moves[i], side);
        if (newscore > score) {
            score = newscore;
            move_index = i;
        }
  // std::cerr << "move index: " << move_index << std::endl;
    }
  best = new Move(moves[move_index]->getX(), moves[move_index]->getY());
  for (unsigned int i; i < moves.size(); i++) {
    delete moves[i];
  }
  return best;
}

int Player::getBestScoreHeuristic(Board * myboard, Move * move, Side side) {
    Board * newboard = myboard->copy();
    // std::cerr << "potential move: " << moves[i].getX() << ", " << moves[i].getY() << std::endl;
    newboard->doMove(move, side);
    int newscore;
    if (side == myside) {
        newscore = newboard->count(myside) - newboard->count(oppside);
    }
    else {
        newscore = newboard->count(oppside) - newboard->count(myside);
    }
    // corner
    if ((move->getX() == 0 || move->getX() == 7) && ((move->getY() == 0 || move->getY() == 7)))   {
        newscore += 15;
        newscore += 4 * (abs(newscore));
    }
    // adjacent to corners
    std::vector<Move> adjacent_corner = {Move(1, 0), Move(0, 1), Move(6, 0), Move(7, 1), 
        Move(0, 6), Move(1, 7), Move(6, 7), Move(7, 6)};

    std::vector<Move> kat_corner = {Move(1, 1), Move(6, 6), Move(6, 1), Move(1, 6)};
    std::vector<Move> sides = {Move(0, 2), Move(0, 3), Move(0, 4), Move(0, 5),
        Move(2, 0), Move(3, 0), Move(4, 0), Move(5, 0), Move(7, 2), Move(7, 3),
        Move(7, 4), Move(7, 5), Move(2, 7), Move(3, 7), Move(4, 7), Move(5, 7)};
    for (unsigned int j = 0; j < adjacent_corner.size(); ++j)   {
        if (move->getX() == adjacent_corner[j].getX() && move->getY() == adjacent_corner[j].getY())   {
            newscore -= 2 * (abs(newscore));
        }
    }
    for (unsigned int j = 0; j < kat_corner.size(); j++) {
        if (move->getX() == kat_corner[j].getX() && move->getY() == kat_corner[j].getY()) {
            newscore -= 3 * (abs(newscore));
        }
    }
    for (unsigned int j = 0; j < sides.size(); j++) {
        if (move->getX() == sides[j].getX() && move->getY() == sides[j].getY()) {
            newscore += 5;
            newscore += sidestability(newboard, side, move);
        //    if ()
            newscore += 2 * (abs(newscore));
        }
    }
    newscore += mobilitycalc(newboard, side);
    return newscore;
    // std::cerr << "score for this move: " << newscore << std::endl;
    // std::cerr << "number on myside: " << newboard->count(myside) << std::endl;
    // std::cerr << "number on oppside: " << newboard->count(oppside) << std::endl;
}

Move *Player::getBestMoveMiniMax(Board * myboard, int depth) {
    std::vector<Move*> moves = getMoves(myboard, myside);
    int bestscore = INT_MIN;
    Move * best;
    int move_index;
    // depth -= 1;
    bool turn = false;
    // if (depth % 2 == 0)   {
    //     turn = true;
    // }
//    bool turn = true;
//    if (depth % 2 == 0)   {
//        turn = false;
//    }
//    if (moves.size() == 1)    {
//        std::cerr << "wew lad" << std::endl;
//        move_index = 0;
//    }
//    else    {
	if (!myboard->hasMoves(myside)) {
	    return nullptr;
	}
        for (unsigned int i = 0; i < moves.size(); i++) {
            std::cerr << "potential move: " << moves[i]->getX() << ", " << moves[i]->getY() << std::endl;
            Board * newboard = myboard->copy();
            newboard->doMove(moves[i], myside);
            std::cerr << "move successfully simulated" << std::endl;
            int score = getMiniMaxScore(newboard, depth, turn);
            std::cerr << "score: " << score << std::endl;
            if (score > bestscore) {
                bestscore = score;
                move_index = i;
            }
        }
//    }
    best = new Move(moves[move_index]->getX(), moves[move_index]->getY());
    std::cerr << "best move: " << best->getX() << ", " << best->getY() << std::endl;
    for (unsigned int i; i < moves.size(); i++) {
        delete moves[i];
    }
    return best;
}
int Player::getMiniMaxScore(Board * myboard, int depth, bool turn) {
    depth -= 1;
    Move *best;
    if (depth == 0) {
        std::cerr << "depth 0" << std::endl;
      	if (turn == true) {
    	    if (myboard->hasMoves(myside)) {
                int score = 1000;
                std::vector<Move*> moves = getMoves(myboard, myside);
                for (unsigned int i = 0; i < moves.size(); i++) {
              	    Board * newboard = myboard->copy();
          	        newboard->doMove(best, myside);
                    int newscore = getBestScoreHeuristic(myboard, moves[i], myside);
                    if (newscore < score) {
                        score = newscore;
                    }
          	    return score;
          	    }
            }
    	    else {
    	        return -1000;
    	    }
    	}
        else {
            if (myboard->hasMoves(oppside)) {
                int score = 1000;
                std::vector<Move*> moves = getMoves(myboard, oppside);
                for (unsigned int i = 0; i < moves.size(); i++) {
                    Board * newboard = myboard->copy();
                    newboard->doMove(best, oppside);
                    int newscore = getBestScoreHeuristic(myboard, moves[i], oppside);
		    newscore *= -1;
                    if (newscore < score) {
                        score = newscore;
                    }
                return score;
                }
            }
            else {
                return 1000;
            }
        }
	}
    // if it's myside's turn
    if (turn == true) {
        std::cerr << "myside's turn" << std::endl;
        std::cerr << "depth: " << depth << std::endl;
	int score = INT_MIN;
	if (myboard->hasMoves(myside)) {
            std::vector<Move*> moves = getMoves(myboard, myside);
            for (unsigned int i = 0; i < moves.size(); i++) {
                Board * newboard = myboard->copy();
                newboard->doMove(moves[i], myside);
                int newscore = getMiniMaxScore(newboard, depth, false);
		        if (newscore > score) {
		          score = newscore;
		        }
            }
	    return score;
	}
	else {
	    return -1000;
	}
    }
    // if it's oppside's turn
    else {
        std::cerr << "oppside's turn" << std::endl;
        std::cerr << "depth: " << depth << std::endl;
	int score = INT_MAX;
	if (myboard->hasMoves(oppside)) {
            std::vector<Move*> moves = getMoves(myboard, oppside);
            for (unsigned int i = 0; i < moves.size(); i++) {
                Board * newboard = myboard->copy();
                newboard->doMove(moves[i], oppside);
                int newscore = getMiniMaxScore(newboard, depth, true);
		if (newscore < score) {
		    score = newscore;
		}
            }
	    return score;
        }
	else {
	    return 1000;
	}
    }
}

std::vector<Move*> Player::getMoves(Board * myboard, Side side) {
    // moves.clear();
    std::vector<Move*> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (myboard->checkMove(&move, side)) {
                Move * move = new Move(i, j);
                moves.push_back(move);
            }
            // moves.push_back(move);
        }
    }
    return moves;
}

int Player::mobilitycalc(Board * myboard, Side side) {
    std::vector<Move*> mymoves;
    std::vector<Move*> oppmoves;
    if (side == myside) {
        mymoves = getMoves(myboard, myside);
        oppmoves = getMoves(myboard, oppside);
    }
    else {
        mymoves = getMoves(myboard, oppside);
        oppmoves = getMoves(myboard, myside);
    }
    return 3 * (mymoves.size() - oppmoves.size());
}

int Player::sidestability(Board * myboard, Side side, Move * move) {
    if (move->getX() > 0 && move->getX() < 7) {
        if (move->getY() == 0) {
            for (unsigned int i = 0; i < 8; i++) {
                if (myboard->occupied(i, 0) == false) {
                    return 0;
                }
            }
            return 15;
        }
        if (move->getY() == 7) {
            for (unsigned int i = 0; i < 8; i++) {
                if(myboard->occupied(i, 7) == false) {
                    return 0;
                }
            }
            return 15;
        }
    }
    if (move->getY() > 0 && move->getY() < 7) {
        if (move->getX() == 0) {
            for (unsigned int i = 0; i < 8; i++) {
                if (myboard->occupied(0, i) == false) {
                    return 0;
                }
            }
            return 15;
        }
        if (move->getX() == 7) {
            for (unsigned int i = 0; i < 8; i++) {
                if(myboard->occupied(7, i) == false) {
                    return 0;
                }
            }
            return 15;
        }
    }

}