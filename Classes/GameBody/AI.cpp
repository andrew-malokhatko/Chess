#include "AI.h"
#include <chrono>
#include <iostream>

namespace AI
{

    Move chooseMove(Board board, bool whiteToMove)
    {
        auto started = std::chrono::system_clock::now();

        Move bestMove;
        int bestValue = INT32_MAX + (int)whiteToMove;
        if (!whiteToMove)
        {
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int boardValue = alphabBetaPruning(newBoard, 2, INT16_MIN, INT16_MAX, true);
                if (boardValue < bestValue)
                {
                    bestValue = boardValue;
                    bestMove = move;
                }
            }
        }
        else
        {
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int boardValue = alphabBetaPruning(newBoard, 2, INT16_MIN, INT16_MAX, false);
                if (boardValue > bestValue)
                {
                    bestValue = boardValue;
                    bestMove = move;
                }
            }
        }

        auto finished = std::chrono::system_clock::now();

        std::cout << "chooseMove: " << std::chrono::duration_cast<std::chrono::milliseconds>(finished - started).count() << "\n";

        return bestMove;
    }

    int alphabBetaPruning(Board board, int depth, int alpha, int beta,  bool maximizingPlayer)
    {
        if (depth == 0)
        {
            return evaluateBoard(board);
        }

        if (maximizingPlayer)
        {
            int maxEval = INT32_MIN;
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int eval = alphabBetaPruning(newBoard, depth - 1, alpha, beta, false); // here pass the board with move done
                maxEval = std::max(eval, maxEval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return maxEval;
        }
        else
        {
            int minEval = INT32_MAX;
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int eval = alphabBetaPruning(newBoard, depth - 1, alpha, beta, true); // here pass the board with move done
                minEval = std::min(eval, minEval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return minEval;
        }
    }

    int evaluateBoard(Board board)
    {
        int res = 0;
        for (int i =0; i < 64; i++)
        {
            res += getPieceValue(board.getPiece(i));
        }
        return res;
    }

}