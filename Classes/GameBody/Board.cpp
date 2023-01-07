#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include "AI.h"
#include "GameBody/Board.h"

Board::Board()
{
    std::fill(board.begin(), board.end(), Piece::None);
}

bool Board::loadposFromFen(std::string fen)
{
    std::map<char, Piece> pieceTypefromSymbol{
        {'k', Piece::BKing}, {'p', Piece::BPawn}, {'n', Piece::BKnight},
        {'b', Piece::BBishop}, {'r', Piece::BRook}, {'q', Piece::BQueen},
        {'K', Piece::WKing}, {'P', Piece::WPawn}, {'N', Piece::WKnight},
        {'B', Piece::WBishop}, {'R', Piece::WRook}, {'Q', Piece::WQueen}
    };

    std::array<Piece, 64> newBoard;
    std::fill(newBoard.begin(), newBoard.end(), Piece::None);

    size_t file = 0;
    size_t rank = 7;
    for (const char ch : fen)
    {
        if (ch == '/')
        {
            rank --;
            file = 0;
            continue;
        }

        if (file >= 8 || rank >= 8)
        {
            // Ill formed FEN string
            return false;
        }

        if (std::isdigit(ch))
        {
            file += ch - '0';
        }
        else
        {
            if (pieceTypefromSymbol.find(ch) == pieceTypefromSymbol.end())
            {
                // Ill formed FEN string
                return false;
            }

            newBoard[Cell{file, rank}] = pieceTypefromSymbol[ch];
            file ++;
        }
    }

    board = newBoard;
    return true;
}

Piece Board::getPiece(size_t index) const
{
    return board[index];
}

void Board::movePiece(Move move)
{
    if (move.specailMove == Move::SpecialMoves::None)
    {
        board[move.to] = std::exchange(board[move.from], Piece::None);
    }
    else
    {
        switch(move.specailMove)
        {
            case Move::SpecialMoves::PromoteToQueen:
                board[move.from] = isWhite(board[move.from]) ? Piece::WQueen : Piece::BQueen;
                board[move.to] = std::exchange(board[move.from], Piece::None);
        }
    }
    whiteToMove = !whiteToMove;
}

std::vector<Move> Board::getMoves(Cell cell) const
{
    std::vector<Move> result;

    Piece piece = board[cell];
    switch (piece)
    {
    case Piece::None:
        break;

    case Piece::BPawn:
    case Piece::WPawn:
        getMovesForPawn(result, cell);
        break;

    case Piece::BBishop:
    case Piece::WBishop:
        getMovesForSlidingPiece(result, SlidingPieceType::Diagonal, cell); // pass a reference to a vector or add to result
        break;

    case Piece::BKnight:
    case Piece::WKnight:
        getMovesForKnight(result, cell);
        break;

    case Piece::BRook:
    case Piece::WRook:
        getMovesForSlidingPiece(result, SlidingPieceType::HorzVert, cell); // pass a reference to a vector or add to result
        break;

    case Piece::BQueen:
    case Piece::WQueen:
        getMovesForSlidingPiece(result, SlidingPieceType::Both, cell); // pass a reference to a vector or add to result
        break;

    case Piece::BKing:
    case Piece::WKing:
        getMovesForKing(result, cell);
        break;
    }    

    return result;
}

std::vector<Move> Board::getMoves() const
{
    std::vector<Move> result;
    for (size_t i = 0; i < 64; i++)
    {
        Piece piece = board[i];
        switch (piece)
        {
        case Piece::None:
            break;

        case Piece::BPawn:
        case Piece::WPawn:
            getMovesForPawn(result, Cell{i});
            break;

        case Piece::BBishop:
        case Piece::WBishop:
            getMovesForSlidingPiece(result, SlidingPieceType::Diagonal, Cell{i}); // pass a reference to a vector or add to result
            break;

        case Piece::BKnight:
        case Piece::WKnight:
            getMovesForKnight(result, Cell{i});
            break;

        case Piece::BRook:
        case Piece::WRook:
            getMovesForSlidingPiece(result, SlidingPieceType::HorzVert, Cell{i}); // pass a reference to a vector or add to result
            break;

        case Piece::BQueen:
        case Piece::WQueen:
            getMovesForSlidingPiece(result, SlidingPieceType::Both, Cell{i}); // pass a reference to a vector or add to result
            break;

        case Piece::BKing:
        case Piece::WKing:
            getMovesForKing(result, Cell{i});
            break;
        }
    }

    return result;
}

std::vector<Move> Board::getLegalMoves(std::vector<Move> moves) const
{
    std::vector<Move> result;
    for (Move move : moves)
    {
        Board newBoard = Board(*this);
        if ((isWhite(board[move.from]) && !whiteToMove) || (isBlack(board[move.from]) && whiteToMove))
        {
            continue;
        }
        newBoard.movePiece(move);
        if (newBoard.isKingInCheck(whiteToMove) == false)
        {
            result.emplace_back(move);
        }
    }
    return result;
}

std::set<Cell> Board::getThreatMap(bool white) const
{
    std::set<Cell> result;
    for (size_t i = 0; i < 64; i++)
    {
        Piece piece = board[i];
        if ((isWhite(piece) && white) || (isBlack(piece) && !white))

        switch (piece)
        {
        case Piece::None:
            break;

        case Piece::BPawn:
        case Piece::WPawn:
            getThreatMapForPawn(result, Cell{i});
            break;

        case Piece::BBishop:
        case Piece::WBishop:
            getThreatMapForSlidingPiece(result, SlidingPieceType::Diagonal, Cell{i}); // pass a reference to a vector or add to result
            break;

        case Piece::BKnight:
        case Piece::WKnight:
            getThreatMapForKnight(result, Cell{i});
            break;

        case Piece::BRook:
        case Piece::WRook:
            getThreatMapForSlidingPiece(result, SlidingPieceType::HorzVert, Cell{i}); // pass a reference to a vector or add to result
            break;

        case Piece::BQueen:
        case Piece::WQueen:
            getThreatMapForSlidingPiece(result, SlidingPieceType::Both, Cell{i}); // pass a reference to a vector or add to result
            break;

        case Piece::BKing:
        case Piece::WKing:
            getThreatMapForKing(result, Cell{i});
            break;
        }
    }
    return result;
}

bool Board::WhiteToMove()
{
    return whiteToMove;
}

bool Board::isKingInCheck(bool white)
{
    std::set<Cell> opponentThreatMap = getThreatMap(!white);
    Cell kingPos;
    for (int i = 0; i < 64; i++)
    {
        if ((white && board[i] == Piece::WKing) || (!white && board[i] == Piece::BKing))
        {
            kingPos = Cell{i};
        }
    }
    for (Cell threatCell : opponentThreatMap)
    {
        if (threatCell == kingPos)
        {
            return true;
        }
    }
    return false;
}

void Board::getMovesForSlidingPiece(std::vector<Move>& result, SlidingPieceType type, Cell pos) const
{
    static constexpr std::array<std::pair<int, int>, 8> directions 
    {
        std::pair(1, 0), std::pair(-1, 0), std::pair(0, 1), std::pair(0, -1),   // Moves for Rook
        std::pair(1, 1), std::pair(-1, -1), std::pair(1, -1), std::pair(-1, 1)  // Moves for bishop
    };

    size_t fromIndex = 0;
    size_t toIndex = 0;

    switch (type)
    {
        case SlidingPieceType::HorzVert:
            fromIndex = 0;
            toIndex = 4;
            break;
        case SlidingPieceType::Diagonal: 
            fromIndex = 4;
            toIndex = 8;
            break;            
        case SlidingPieceType::Both:
            fromIndex = 0;
            toIndex = 8;
            break;             
    }

    result.reserve(8);

    const Piece piece = board[pos];
    for (size_t i = fromIndex; i < toIndex; i++)
    {
        Cell curPos = pos;

        while(true)
        {
            curPos = Cell(curPos.x() + directions[i].first, curPos.y() + directions[i].second);
            if (curPos.isValid() == false)
            {
                break;
            }

            const Piece toMovePiece = board[curPos];
            if (toMovePiece != Piece::None)
            {
                if (sameColor(toMovePiece, piece) == false)
                {
                    result.emplace_back(Move{pos, curPos});
                }

                break;
            }

            result.emplace_back(Move{pos, curPos});
        }
    }
}

void Board::getMovesForKing(std::vector<Move>& result, Cell pos) const
{
    static constexpr std::array<std::pair<int, int>, 8> moves
    {
        std::pair{1, 0}, std::pair{-1, 0}, std::pair{0, 1}, std::pair{0, -1},
        std::pair{1, 1}, std::pair{-1, -1}, std::pair{1, -1}, std::pair{-1, 1}
    };

    result.reserve(4);

    Piece piece = board[pos];
    for (const auto [x, y] : moves)
    {
        Cell toMoveSquare{pos.x() + x, pos.y() + y};
        if (toMoveSquare.isValid() == false) 
        {
            continue;
        }

        const Piece toMovePiece = board[toMoveSquare];
        if (toMovePiece != Piece::None && sameColor(toMovePiece, piece) == true)
        {
            continue;
        }

        result.emplace_back(Move{pos, toMoveSquare});
    }
}

void Board::getMovesForKnight(std::vector<Move>& result, Cell pos) const
{
    static constexpr std::array<std::pair<int, int>, 8> moves
    {
        std::pair{1, 2}, std::pair{2, 1}, std::pair{2, -1}, std::pair{1, -2},
        std::pair{-1, 2}, std::pair{-2, 1}, std::pair{-2, -1}, std::pair{-1, -2}
    };

    result.reserve(4);

    Piece piece = board[pos];
    for (const auto [x, y] : moves)
    {   
        Cell toMoveSquare{pos.x() + x, pos.y() + y};
        if (toMoveSquare.isValid() == false) 
        {
            continue;
        }

        const Piece toMovePiece = board[toMoveSquare];
        if (toMovePiece != Piece::None && sameColor(toMovePiece, piece) == true)
        {
            continue;
        }

        result.emplace_back(Move{pos, toMoveSquare});
    }
}

void Board::getMovesForPawn(std::vector<Move>& result, Cell pos) const
{
    Piece piece = board[pos];
    int startRank = isWhite(piece) ? 1 : 6;
    int direction = isWhite(piece) ? 1 : -1;
    int rank = pos.y();
    int file = pos.x() ;

    int rankBeforePromotion = isWhite(piece) ? 6 : 1;
    bool oneStepBeforePromotion = rank == rankBeforePromotion;

    result.reserve(2);

    //forward moves
    if (board[Cell(file, rank + direction)] == Piece::None)
    {
        if (oneStepBeforePromotion)
        {
            result.emplace_back(Move{pos, Cell(file, rank + direction), Move::SpecialMoves::PromoteToQueen});
        }
        else
        {
            result.emplace_back(Move{pos, Cell{file, rank + direction}.getIndex()});
        }
        if (pos.y() == startRank && board[Cell(pos.x(), pos.y() + direction * 2)]  == Piece::None)
        {
            result.emplace_back(Move{pos, Cell(pos.x(), pos.y() + direction * 2)});
        }
    }

    //captures
    Cell captureMove;
    captureMove.fromPos(file + direction, rank + direction);

    if (captureMove.isValid() == true)
    {
        Piece toMovePiece = board[captureMove];
        if (toMovePiece != Piece::None && !sameColor(piece, toMovePiece))
        {
            if (oneStepBeforePromotion)
            {
                result.emplace_back(Move{pos, captureMove, Move::SpecialMoves::PromoteToQueen});
            }
            else
            {
                result.emplace_back(Move{pos, captureMove});
            }
        }
    }

    captureMove.fromPos(file - direction, rank + direction);
    if (captureMove.isValid() == true)
    {
        Piece toMovePiece = board[captureMove];
        if (toMovePiece != Piece::None && !sameColor(piece, toMovePiece))
        {
            if (oneStepBeforePromotion)
            {
                result.emplace_back(Move{pos, captureMove, Move::SpecialMoves::PromoteToQueen});
            }
            else
            {
                result.emplace_back(Move{pos, captureMove});
            }
        }
    }
}


void Board::getThreatMapForSlidingPiece(std::set<Cell>& result, SlidingPieceType type, Cell pos) const
{
    static constexpr std::array<std::pair<int, int>, 8> directions 
    {
        std::pair(1, 0), std::pair(-1, 0), std::pair(0, 1), std::pair(0, -1),   // Moves for Rook
        std::pair(1, 1), std::pair(-1, -1), std::pair(1, -1), std::pair(-1, 1)  // Moves for bishop
    };

    size_t fromIndex = 0;
    size_t toIndex = 0;

    switch (type)
    {
        case SlidingPieceType::HorzVert:
            fromIndex = 0;
            toIndex = 4;
            break;
        case SlidingPieceType::Diagonal: 
            fromIndex = 4;
            toIndex = 8;
            break;            
        case SlidingPieceType::Both:
            fromIndex = 0;
            toIndex = 8;
            break;             
    }

    const Piece piece = board[pos];
    for (size_t i = fromIndex; i < toIndex; i++)
    {
        Cell curPos = pos;

        while(true)
        {
            curPos = Cell(curPos.x() + directions[i].first, curPos.y() + directions[i].second);
            if (curPos.isValid() == false)
            {
                break;
            }

            const Piece toMovePiece = board[curPos];
            if (toMovePiece != Piece::None)
            {
                result.emplace(curPos);
                break;
            }

            result.emplace(curPos);
        }
    }
}

void Board::getThreatMapForKing(std::set<Cell>& result, Cell pos) const
{
    static constexpr std::array<std::pair<int, int>, 8> moves
    {
        std::pair{1, 0}, std::pair{-1, 0}, std::pair{0, 1}, std::pair{0, -1},
        std::pair{1, 1}, std::pair{-1, -1}, std::pair{1, -1}, std::pair{-1, 1}
    };

    Piece piece = board[pos];
    for (const auto [x, y] : moves)
    {
        Cell toMoveSquare{pos.x() + x, pos.y() + y};
        if (toMoveSquare.isValid() == false) 
        {
            continue;
        }

        result.emplace(toMoveSquare);
    }
}

void Board::getThreatMapForKnight(std::set<Cell>& result, Cell pos) const
{
    static constexpr std::array<std::pair<int, int>, 8> moves
    {
        std::pair{1, 2}, std::pair{2, 1}, std::pair{2, -1}, std::pair{1, -2},
        std::pair{-1, 2}, std::pair{-2, 1}, std::pair{-2, -1}, std::pair{-1, -2}
    };

    Piece piece = board[pos];
    for (const auto [x, y] : moves)
    {   
        Cell toMoveSquare{pos.x() + x, pos.y() + y};
        if (toMoveSquare.isValid() == false) 
        {
            continue;
        }

        result.emplace(toMoveSquare);
    }
}

void Board::getThreatMapForPawn(std::set<Cell>& result, Cell pos) const
{
    if (pos == 15)
    {
        int dima = 0;
    }
    Piece piece = board[pos];
    int startRank = isWhite(piece) ? 1 : 6;
    int direction = isWhite(piece) ? 1 : -1;
    int rank = pos.y();
    int file = pos.x() ;

    int rankBeforePromotion = isWhite(piece) ? 6 : 1;
    bool oneStepBeforePromotion = rank == rankBeforePromotion;

    //captures
    Cell captureMove;
    bool valid = captureMove.fromPos(file + direction, rank + direction);
    if (valid == true)
    {
        result.emplace(captureMove);
    }

    valid = captureMove.fromPos(file - direction, rank + direction);
    if (valid == true)
    {
        result.emplace(captureMove);
    }
}

Move Board::AIMovePiece()
{
    return AI::chooseMove(*this, whiteToMove);
}