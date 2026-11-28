#include <iostream>

#include "chess/types.hpp"
#include "chess/bitboard.hpp"
#include "chess/board.hpp"
#include "chess/input.hpp"

bool validMove(const BoardState& board, const std::string& curr, const std::string& targ, Bitboard& curr_square, Bitboard& targ_square, std::string& error) {

  if (curr == targ) {
    error = "invalid move: cant move nowhere!";
    return false;
  }

  if (curr.length() != 2 || targ.length() != 2) {
    error = "invalid move: incorrect move length";
    return false;
  }
 
  std::string move = curr + targ;
  for (int i = 0; i < 4; ++i) {
    if (i % 2 != 0) {
      if (move[i] - '1' < 0 || move[i] - '1' > 7) {
        error = "invalid move: rank not in range";
        return false;
      }
    }
    else {
      if(move[i] - 'a' < 0 || move[i] - 'a' > 7) {
        error = "invalid move: file not in range";
          return false;
      }
    }
  }

  int currFile = curr[0] - 'a';
  int currRank = curr[1] - '1';
  int targFile = targ[0] - 'a';
  int targRank = targ[1] - '1';

  curr_square = sq_bb(currRank, currFile);
  targ_square = sq_bb(targRank, targFile);

  PieceInfo mover = getPieceType(board, curr_square);
 
  // validate white pawn move
  if (mover.color == WHITE && mover.type == PAWN) {
    int curr_rank = rank_of_bb(curr_square);
    int targ_rank = rank_of_bb(targ_square);
    int curr_file = file_of_bb(curr_square);
    int targ_file = file_of_bb(targ_square);

    if (board.sideToMove == BLACK) {
      error = "invalid move: black cant move whites pieces!";
      return false;
    }

    if (curr_rank+1 == targ_rank && curr_file == targ_file) {
      PieceInfo U1SquareInfo = getPieceType(board, targ_square);
      if (U1SquareInfo.type != NONE) {
        error = "invalid move: piece in the way!";
        return false;
      }
      return true;
    }

    if (targ_rank == curr_rank+2) {
      if (curr_rank == 1) {
        PieceInfo U1SquareInfo = getPieceType(board, targ_square >> 8);
        PieceInfo U2SquareInfo = getPieceType(board, targ_square);
        if (U1SquareInfo.type != NONE || U2SquareInfo.type != NONE) {
          error = "invalid move: piece in the way!";
          return false;
        }
        return true;
      }
      else {
        error = "invalid move: pawn cant move that far off starting square!";
        return false;
      }
    }
    else if (targ_rank < curr_rank) {
      error = "invalid move: pawns cant move backward!";
      return false;
    }
    else if (targ_rank > curr_rank+2) {
      error = "invalid move: pawns cant move that far!";
      return false;
    }

    Bitboard LDiagCaptureSquare = 0ULL;
    Bitboard RDiagCaptureSquare = 0ULL;

    if (curr_rank < 7) {
      if (curr_file != 0) LDiagCaptureSquare = sq_bb(curr_rank+1, curr_file-1); 
      if (curr_file != 7) RDiagCaptureSquare = sq_bb(curr_rank+1, curr_file+1);
    }

    PieceInfo LDiagCaptureSquareInfo = getPieceType(board, LDiagCaptureSquare);
    PieceInfo RDiagCaptureSquareInfo = getPieceType(board, RDiagCaptureSquare);

    if ((targ_rank == curr_rank + 1) && (targ_file == curr_file-1)) {
      if (LDiagCaptureSquareInfo.type == NONE) {
        error = "invalid move: no piece to capture!";
        return false;
      }
      else if (LDiagCaptureSquareInfo.color != BLACK) {
        error = "invalid move: cant capture a friendly piece!";
        return false;
      }
      return true;
    } 
    if ((targ_rank == curr_rank + 1) && (targ_file == curr_file+1)) {
      if (RDiagCaptureSquareInfo.type == NONE) {
        error = "invalid move: no piece to capture!";
        return false;
      }
      else if (RDiagCaptureSquareInfo.color != BLACK) {
        error = "invalid move: cant capture a friendly piece!";
        return false;
      }
    }
    else if (targ_file != curr_file) {
      error = "invalid move: pawns cant move sideways!";
      return false;
    }
  }
  return true;
}