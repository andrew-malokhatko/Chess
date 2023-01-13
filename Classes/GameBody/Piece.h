#pragma once
#include <cinttypes>

using PieceType = uint8_t;

enum class Piece : PieceType
{
    Black = 0x10,

    None = 0,
    WKing = 1,
    WPawn = 2,
    WKnight = 3,
    WBishop = 4,
    WRook = 5,
    WQueen = 6,
    
    BKing = WKing | Black,
    BPawn = WPawn | Black,
    BKnight = WKnight | Black,
    BBishop = WBishop | Black,
    BRook = WRook | Black,
    BQueen = WQueen | Black
};

bool isBlack(Piece piece);
bool isWhite(Piece piece);
bool sameColor(Piece piece1, Piece piece2);

const char* getPieceName(Piece piece);
int getPieceValue(Piece piece);
