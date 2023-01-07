#pragma once
#include "Board.h"

namespace AI
{
    Move chooseMove(Board board, bool whiteToMove);
    int alphabBetaPruning(Board board, int depth, int alpha, int beta,  bool maximizingPlayer);
    int evaluateBoard(Board board);
};