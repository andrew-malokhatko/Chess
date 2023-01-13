#pragma once
#include <cstddef>


struct Move
{
    enum class SpecialMoves
    {
        None = 0,
        PromoteToQueen = 1,
        PromoteToKnight = 2,
        PromoteToBishop = 3,
        PromoteToRook = 4,
        KingMove = 5
    };

    size_t from = 0;
    size_t to = 0;
    SpecialMoves specailMove = SpecialMoves::None;
};