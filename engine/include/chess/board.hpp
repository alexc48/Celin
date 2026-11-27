#pragma once

#include "chess/types.hpp"

struct BoardState {
  Bitboard pieces[2][6] = {};

  BoardState();
};

PieceInfo getPieceType(BoardState board, Bitboard bit);
void move(BoardState& board, Bitboard curr_square, Bitboard targ_square, int moveCount);