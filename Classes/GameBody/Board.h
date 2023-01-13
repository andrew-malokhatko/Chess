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
    void setPiece(size_t index, Piece piece);
    
    void movePiece(Move move);

    bool WhiteToMove();
    bool isKingInCheck(bool white);

    std::vector<Move> getLegalMoves(std::vector<Move> moves) const;
    //moves for pieces
    std::vector<Move> getMoves(Cell cell) const;
    std::vector<Move> getMoves() const; // here generating moves
    void getMovesForSlidingPiece(std::vector<Move>& result, size_t fromIndex, size_t toIndex, Cell pos) const;
    void getMovesForKing(std::vector<Move>& result, Cell pos) const;
    void getMovesForKnight(std::vector<Move>& result, Cell pos) const;
    void getMovesForPawn(std::vector<Move>& result, Cell pos) const;
    void getPromotionMoves(Cell from, Cell to);

    //threatMaps for pieces
    uint64_t getThreatMap(bool white);
    uint64_t getThreatMapForSlidingPiece(size_t fromIndex, size_t toIndex, Cell pos) const;
    uint64_t getThreatMapForKing(Cell pos) const;
    uint64_t getThreatMapForKnight(Cell pos) const;
    uint64_t getThreatMapForPawn(Cell pos) const;
    //special Moves
    /*bool hasQueenSideCastle();
    bool hasKingSideCastle();*/

    Move AIMovePiece();

private:
    bool whiteToMove = true;
    Cell whiteKingPos = Cell("e1");
    Cell blackKingPos = Cell("e8");
    //uint castleMask = 0;
    /*bool leftSideCastle = true; // left rook and king havent moved
    bool rightSideCasstle = true; // right rook and king havent moved*/

    /*unsigned long long whiteThreatMap; // every board should have its own threat map that will 
    unsigned long long backThreatMap;*/  // slightly change after a move
    std::array<Piece, 64> board;
};

// i hope i wont forget to read this
// somehow there are more then one king after moving one