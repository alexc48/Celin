#pragma once

#include "chess/types.hpp"
#include "chess/board.hpp"

struct BoardState {
  Bitboard pieces[2][6] = {};

  Color sideToMove = WHITE;
  u8 enpassantSquare = NO_SQUARE;
  bool whiteCanCastleKingside = true;
  bool whiteCanCastleQueenside = true;
  bool blackCanCastleKingside = true;
  bool blackCanCastleQueenside = true;
  u16 fullMoveCount = 1;
  BoardState();
};

PieceInfo getPieceType(BoardState board, Bitboard bit);
void move(BoardState& board, Bitboard curr_square, Bitboard targ_square);

Bitboard occupancy(const BoardState& board, Color color);