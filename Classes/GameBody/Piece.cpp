#include <cassert>
#include <cstddef>
#include "Piece.h"

bool isBlack(Piece piece)  
{   
    return static_cast<PieceType>(piece) & static_cast<PieceType>(Piece::Black) ? true : false;
}

bool isWhite(Piece piece)  
{   
    return !isBlack(piece);
}

bool sameColor(Piece piece1, Piece piece2)
{
    return (static_cast<PieceType>(piece1) & static_cast<PieceType>(Piece::Black)) == 
           (static_cast<PieceType>(piece2) & static_cast<PieceType>(Piece::Black));
}

const char* getPieceName(Piece piece)
{
    switch (piece)
    {
        case Piece::None: return "None";
        case Piece::WKing: return "WKing";
        case Piece::WPawn: return "WPawn";
        case Piece::WKnight: return "WKnight";
        case Piece::WBishop: return "WBishop";
        case Piece::WRook: return "WRook";
        case Piece::WQueen: return "WQueen";

        case Piece::BKing: return "BKing";
        case Piece::BPawn: return "BPawn";
        case Piece::BKnight: return "BKnight";
        case Piece::BBishop: return "BBishop";
        case Piece::BRook: return "BRook";
        case Piece::BQueen: return "BQueen";

        default:
            assert(false);
            return "Unknown";
    }
}

int getPieceValue(Piece piece)
{
    static constexpr int values[24] = 
    {
        0, 1000, 10, 30, 30, 50, 90, -1, 
        -1, -1, -1, -1, -1, -1, -1, -1, 
        -1, -1000, -10, -30, -30, -50, -90, -1
    };

    return values[static_cast<size_t>(piece)];
}

