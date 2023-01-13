#include "AI.h"
#include <chrono>
#include <iostream>

namespace AI
{

    Move chooseMove(Board board, bool whiteToMove)
    {
        auto started = std::chrono::system_clock::now();
        int t;

        Move bestMove;
        int bestValue = INT32_MAX + (int)whiteToMove;
        if (!whiteToMove)
        {
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int boardValue = alphabBetaPruning(newBoard, 2, INT16_MIN, INT16_MAX, true, t);
                //int boardValue = minimax(newBoard, 2, true, t);
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
                int boardValue = alphabBetaPruning(newBoard, 3, INT16_MIN, INT16_MAX, false, t);
                if (boardValue > bestValue)
                {
                    bestValue = boardValue;
                    bestMove = move;
                }
            }
        }

        auto finished = std::chrono::system_clock::now();

        std::cout << "chooseMove: " << std::chrono::duration_cast<std::chrono::milliseconds>(finished - started).count() << "\n";
        std::cout << "Nodes visited: " << t << "\n" << "\n";

        return bestMove;
    }

    int alphabBetaPruning(const Board& board, int depth, int alpha, int beta,  bool maximizingPlayer, int& t)
    {
        t++;
        if (depth == 0)
        {
            return evaluateBoard(board);
        }

        Board newBoard = board;

        if (maximizingPlayer)
        {
            int maxEval = INT32_MIN;
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int eval = alphabBetaPruning(newBoard, depth - 1, alpha, beta, false, t); // here pass the board with move done
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
                int eval = alphabBetaPruning(newBoard, depth - 1, alpha, beta, true, t); // here pass the board with move done
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

    int minimax(const Board& board, int depth,  bool maximizingPlayer, int& t)
    {
        t++;
        if (depth == 0)
        {
            return evaluateBoard(board);
        }

        Board newBoard = board;

        if (maximizingPlayer)
        {
            int maxEval = INT32_MIN;
            for (Move move : board.getLegalMoves(board.getMoves()))
            {
                Board newBoard = Board(board);
                newBoard.movePiece(move);
                int eval = minimax(newBoard, depth - 1, false, t); // here pass the board with move done
                maxEval = std::max(eval, maxEval);
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
                int eval = minimax(newBoard, depth - 1, true, t); // here pass the board with move done
                minEval = std::min(eval, minEval);
            }
            return minEval;
        }
    }

    int evaluateBoard(const Board& board)
    {
        int res = 0;
        for (int i = 0; i < 64; i++)
        {
            res += getPieceValue(board.getPiece(i));
        }
        return res;
    }

}