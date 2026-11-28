#pragma once

#include "types.hpp"
#include "misc.hpp"

#include <cstddef>

enum MoveType : u8 {
      NORMAL,
      DOUBLE_PAWN_PUSH,
      CASTLE,
      EN_PASSANT,
};

struct Move {
   u8 curr_square = NO_SQUARE;
   u8 targ_square = NO_SQUARE;
   PieceType promotion_piece = NONE;

   MoveType move_type = NORMAL;
};

struct MoveList {
      static constexpr std::size_t MAX_MOVES = 256;

      Move moves[MAX_MOVES];

      std::size_t count = 0;

      void addMove(u8 curr_square, u8 targ_square, PieceType promotion_piece = NONE, MoveType move_type = NORMAL) {
         moves[count].curr_square = curr_square;
         moves[count].targ_square = targ_square;
         moves[count].promotion_piece = promotion_piece;
         moves[count].move_type = move_type;
         ++count;
      }

};