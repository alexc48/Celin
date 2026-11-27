#include <iostream>

#include "chess/types.hpp"
#include "chess/bitboard.hpp"
#include "chess/board.hpp"
#include "chess/input.hpp"

bool validMove(const BoardState& board, const std::string& curr, const std::string& targ, Bitboard& curr_square, Bitboard& targ_square, const int& moveCount) {

  if (curr == targ) {
    std::cout << "invalid move: cant move nowhere!\n";
    return false;
  }

  if (curr.length() != 2 || targ.length() != 2) {
    std::cout << "invalid move: incorrect move length\n";
    return false;
  }
 
  std::string move = curr + targ;
  for (int i = 0; i < 4; ++i) {
    if (i % 2 != 0) {
      if (move[i] - '1' < 0 || move[i] - '1' > 7) {
        std::cout << "invalid move: rank not in range\n";
        return false;
      }
    }
    else {
      if(move[i] - 'a' < 0 || move[i] - 'a' > 7) {
        std::cout << "invalid move: file not in range\n";
          return false;
      }
    }
  }

  int currFile = curr[0] - 'a';
  int currRank = curr[1] - '1';
  int targFile = targ[0] - 'a';
  int targRank = targ[1] - '1';

  curr_square = sq(currRank, currFile);
  targ_square = sq(targRank, targFile);

  PieceInfo mover = getPieceType(board, curr_square);
 
  // validate white pawn move
  if (mover.color == WHITE && mover.type == PAWN) {
    int curr_rank = rank_of(curr_square);
    int targ_rank = rank_of(targ_square);
    int curr_file = file_of(curr_square);
    int targ_file = file_of(targ_square);

    if (blacksTurn(moveCount)) {
      std::cout << "invalid move: black cant move whites pieces!\n";
      return false;
    }

    Bitboard U1Square = 0ULL;
    Bitboard U2Square = 0ULL;

    if (targ_rank < 7) {
      U1Square = sq(curr_rank+8, curr_file);
    }
    if (targ_rank < 6 ) {
      U2Square = sq(targ_rank+16, curr_file);
    }

    if (curr_rank+1 == targ_rank && curr_file == targ_file) {
      PieceInfo U1SquareInfo = getPieceType(board, targ_square);
      if (U1SquareInfo.type != NONE) {
        std::cout << "invalid move: piece in the way!\n";
        return false;
      }
      return true;
    }

    if (targ_rank == curr_rank+2) {
      if (curr_rank == 1) {
        PieceInfo U1SquareInfo = getPieceType(board, targ_square >> 8);
        PieceInfo U2SquareInfo = getPieceType(board, targ_square);
        if (U1SquareInfo.type != NONE || U2SquareInfo.type != NONE) {
          std::cout << "invalid move: piece in the way!\n";
          return false;
        }
        return true;
      }
      else {
        std::cout << "invalid move: pawn cant move that far off starting square!\n";
        return false;
      }
    }
    else if (targ_rank < curr_rank) {
      std::cout << "invalid move: pawns cant move backward!\n";
      return false;
    }
    else if (targ_rank > curr_rank+2) {
      std::cout << "invalid move: pawns cant move that far!\n";
      return false;
    }

    Bitboard LDiagCaptureSquare = 0ULL;
    Bitboard RDiagCaptureSquare = 0ULL;

    if (curr_rank < 7) {
      if (curr_file != 0) LDiagCaptureSquare = sq(curr_rank+1, curr_file-1); 
      if (curr_file != 7) RDiagCaptureSquare = sq(curr_rank+1, curr_file+1);
    }

    PieceInfo LDiagCaptureSquareInfo = getPieceType(board, LDiagCaptureSquare);
    PieceInfo RDiagCaptureSquareInfo = getPieceType(board, RDiagCaptureSquare);

    if ((targ_rank == curr_rank + 1) && (targ_file == curr_file-1)) {
      if (LDiagCaptureSquareInfo.type == NONE) {
        std::cout << "invalid move: no piece to capture!\n";
        return false;
      }
      else if (LDiagCaptureSquareInfo.color != BLACK) {
        std::cout << "invalid move: cant capture a friendly piece!\n";
        return false;
      }
      return true;
    } 
    if ((targ_rank == curr_rank + 1) && (targ_file == curr_file+1)) {
      if (RDiagCaptureSquareInfo.type == NONE) {
        std::cout << "invalid move: no piece to capture!\n";
        return false;
      }
      else if (RDiagCaptureSquareInfo.color != BLACK) {
        std::cout << "invalid move: cant capture a friendly piece!\n";
        return false;
      }
    }
    else if (targ_file != curr_file) {
      std::cout << "invalid move: pawns cant move sideways!\n";
      return false;
    }
  }
  return true;
}