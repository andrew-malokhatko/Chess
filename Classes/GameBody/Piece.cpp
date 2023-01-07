#include <cassert>
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
    switch (piece)
    {
        case Piece::None: return 0;
        case Piece::WKing: return 1000;
        case Piece::WPawn: return 10;
        case Piece::WKnight: return 30;
        case Piece::WBishop: return 30;
        case Piece::WRook: return 50;
        case Piece::WQueen: return 90;

        case Piece::BKing: return -1000;
        case Piece::BPawn: return -10;
        case Piece::BKnight: return -30;
        case Piece::BBishop: return -30;
        case Piece::BRook: return -50;
        case Piece::BQueen: return -90;

        default:
            assert(false);
            return 0;
    }
}

