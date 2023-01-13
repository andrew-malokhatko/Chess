#pragma once
#include "Board.h"

namespace AI
{
    Move chooseMove(Board board, bool whiteToMove);
    int alphabBetaPruning(const Board& board, int depth, int alpha, int beta,  bool maximizingPlayer, int& t);
    int minimax(const Board& board, int depth, bool maximizingplayer, int& t);
    int evaluateBoard(const Board& board);
};