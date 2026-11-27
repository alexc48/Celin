#include "chess/bitboard.hpp"
#include "chess/board.hpp"

BoardState::BoardState() {
  pieces[WHITE][PAWN] = 0xFFULL << 8;
  pieces[BLACK][PAWN] = 0xFFULL << 48;
  pieces[WHITE][KNIGHT] = sq(0, 1) | sq(0, 6);
  pieces[BLACK][KNIGHT] = sq(7, 1) | sq(7, 6);
  pieces[WHITE][BISHOP] = sq(0,2) | sq(0, 5);
  pieces[BLACK][BISHOP] = sq(7,2) | sq(7, 5);
  pieces[WHITE][ROOK] = sq(0,0) | sq(0,7);
  pieces[BLACK][ROOK] = sq(7, 0) | sq(7, 7);
  pieces[WHITE][QUEEN] = sq(0, 3);
  pieces[BLACK][QUEEN] = sq(7, 3);
  pieces[WHITE][KING] = sq(0, 4);
  pieces[BLACK][KING] = sq(7, 4);
}

PieceInfo getPieceType(BoardState board, Bitboard bit) {

  for (int color = 0; color < 2; ++color) {
    for (int piece = 0; piece < 6; ++piece) {
      if (board.pieces[color][piece] & bit) {
        return { (Color)color, (PieceType)piece};
      }
    }
  }
  return {WHITE, NONE};
}

void move(BoardState& board, Bitboard curr_square, Bitboard targ_square, int moveCount) {

  PieceInfo mover = getPieceType(board, curr_square);
  PieceInfo victim = getPieceType(board, targ_square);

  if (mover.type == NONE) return;

  if (victim.type != NONE) board.pieces[victim.color][victim.type] &= ~targ_square;

  PieceType original_type = mover.type;

  if (mover.type == PAWN && mover.color == WHITE) {
    if (rank_of(targ_square) == 7) mover.type = QUEEN;
  }

   board.pieces[mover.color][original_type] &= ~curr_square;
   board.pieces[mover.color][mover.type] |= targ_square;
}
