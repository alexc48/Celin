#pragma once

#include <cstdint>

enum Color {
  WHITE,
  BLACK
};

enum PieceType {
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

using Bitboard = uint64_t;
