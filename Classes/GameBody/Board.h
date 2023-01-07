#pragma once

#include <array>
#include <vector>
#include <set>
#include "Cell.h"
#include "Move.h"
#include "Piece.h"

enum class SlidingPieceType
{
    HorzVert,
    Diagonal,
    Both
};

class Board
{
public:
    Board();
    bool loadposFromFen(std::string fen); // https://www.chess.com/terms/fen-chess
    Piece getPiece(size_t index) const; // returns a piece by index!
    void movePiece(Move move);

    std::vector<Move> getMoves(Cell cell) const;
    std::vector<Move> getMoves() const; // here generating moves
    std::vector<Move> getLegalMoves(std::vector<Move> moves) const;
    std::set<Cell> getThreatMap(bool white) const;
    bool WhiteToMove();
    bool isKingInCheck(bool white);

    //moves for pieces
    void getMovesForSlidingPiece(std::vector<Move>& result, SlidingPieceType type, Cell pos) const;
    void getMovesForKing(std::vector<Move>& result, Cell pos) const;
    void getMovesForKnight(std::vector<Move>& result, Cell pos) const;
    void getMovesForPawn(std::vector<Move>& result, Cell pos) const;
    void getPromotionMoves(Cell from, Cell to);

    //threatMaps for pieces
    void getThreatMapForSlidingPiece(std::set<Cell>& result, SlidingPieceType type, Cell pos) const;
    void getThreatMapForKing(std::set<Cell>& result, Cell pos) const;
    void getThreatMapForKnight(std::set<Cell>& result, Cell pos) const;
    void getThreatMapForPawn(std::set<Cell>& result, Cell pos) const;
    //special Moves
    /*bool hasQueenSideCastle();
    bool hasKingSideCastle();*/

    Move AIMovePiece();

private:
    bool whiteToMove = true;
    //uint castleMask = 0;
    /*bool leftSideCastle = true; // left rook and king havent moved
    bool rightSideCasstle = true; // right rook and king havent moved*/

    /*unsigned long long whiteThreatMap; // every board should have its own threat map that will 
    unsigned long long backThreatMap;*/  // slightly change after a move
    std::array<Piece, 64> board;
};