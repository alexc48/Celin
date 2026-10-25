#include <iostream>
#include <bitset>
#include <string>
#include <cstdint>
#include <bit>

#include "chess/types.hpp"

const std::string SYMBOLS[2][6] = {
  {"♙", "♘", "♗", "♖", "♕", "♔"},  // white
  {"♟", "♞", "♝", "♜", "♛", "♚"}   // black
};

uint64_t sq(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}

struct BoardState {
  uint64_t pieces[2][6] = {};

  BoardState() {
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
};

PieceInfo getPieceType(BoardState board, uint64_t bit) {

  for (int color = 0; color < 2; ++color) {
    for (int piece = 0; piece < 6; ++piece) {
      if (board.pieces[color][piece] & bit) {
        return { (Color)color, (PieceType)piece};
      }
    }
  }
  return {WHITE, NONE};
}

// turns bitboard into a correctly oriented board string
std::string bb_to_str(std::bitset<64> bb) {
  std::string flipped(64, '0');
  std::string bb_str = bb.to_string();
  int i = 0;
  for(int row = 0; row < 8; ++row) {
    for (int col = 7; col >= 0; --col) {
      flipped[i] = bb_str[row * 8 + col];
      i++;
    }
  }
  return flipped;
}

void printBitboard(std::bitset<64> pieceBitboard) {
  std::string bb = bb_to_str(pieceBitboard);
  for (int i = 0; i < 64; ++i) { if ((i % 8 == 0) && i != 0) {
      std::cout << '\n';
    }
    std::cout << bb[i] << ' ';
  }
  std::cout << '\n';
}

void printBoard(const BoardState& board) {
  for (int rank = 7; rank >= 0; --rank) {
    std::cout << '\n';
    std::cout << rank+1 << ' ';
    for (int file = 0; file < 8; ++file) {
      PieceInfo p = getPieceType(board, sq(rank, file));
      std::cout << (p.type == NONE ? "·" : SYMBOLS[p.color][p.type]) << ' ';
    }
  }
  std::cout << '\n';
  std::cout << "  a b c d e f g h\n";
}

int rank_of(uint64_t bb) {
  return std::countr_zero(bb) >> 3;
}

int file_of(uint64_t bb) {
  return std::countr_zero(bb) & 7;
}

void getMove(std::string& curr, std::string& targ, const int& moveCount) {
  std::cout << "Move #" << moveCount << '\n';
  std::cout << (!(moveCount % 2 == 0) ? "Whites Move: " : "Blacks Move") << std::endl;
  std::cin >> curr >> targ;
}

bool blacksTurn(const int& moveCount) {
  return (moveCount % 2 == 0);
}

bool validMove(const BoardState& board, const std::string& curr, const std::string& targ, uint64_t& curr_square, uint64_t& targ_square, const int& moveCount) {

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

    uint64_t U1Square = 0ULL;
    uint64_t U2Square = 0ULL;

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

    uint64_t LDiagCaptureSquare = 0ULL;
    uint64_t RDiagCaptureSquare = 0ULL;

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
void move(BoardState& board, uint64_t curr_square, uint64_t targ_square, int moveCount) {

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
void clear() {
    std::cout <<  "\033[2J\033[H" << std::flush;
}

int main() {

  clear();
  BoardState board;
  printBoard(board);
  int moveCount = 0;

  while (true) {
    ++moveCount;
    std::string curr, targ;
    uint64_t curr_square = -1;
    uint64_t targ_square = -1;

    getMove(curr, targ, moveCount);
    while (!validMove(board, curr, targ, curr_square, targ_square, moveCount)) {
      getMove(curr, targ, moveCount);
    }

    move(board, curr_square, targ_square, moveCount);
    
    clear();
    printBoard(board);
  }
}
