#pragma once

#include "misc.hpp"

enum Color : u8 {
  WHITE,
  BLACK
};

enum PieceType : u8 {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    NONE
};

struct PieceInfo {
  Color color;
  PieceType type;
};

using Bitboard = u64;