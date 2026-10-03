#include <iostream>
#include <bitset>
#include <string>
#include <cstdint>

// Bit board layout:
//a1 = bit 0, h1 = bit 7, a8 = bit 56, h8 = bit 63

const std::string SYMBOLS[2][6] = {
  {"♙", "♘", "♗", "♖", "♕", "♔"},  // white
  {"♟", "♞", "♝", "♜", "♛", "♚"}   // black
};

enum Color     {WHITE, BLACK};
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

uint64_t sq(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}

struct BoardState {
  // piece[color][type] -> bitboard
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

struct PieceInfo {
  Color color;
  PieceType type;
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
    for (int file = 0; file < 8; ++file) {
      PieceInfo p = getPieceType(board, sq(rank, file));
      std::cout << (p.type == NONE ? "·" : SYMBOLS[p.color][p.type]) << ' ';
    }
  }
  std::cout << '\n';
}

bool validMove(const BoardState& board, const uint64_t curr_square, const uint64_t targ_square) {
  return true;
}
void move(const std::string& curr, const std::string& targ, BoardState& board) {
  int currFile = curr[0] - 'a';
  int currRank = curr[1] - '1';
  int targFile = targ[0] - 'a';
  int targRank = targ[1] - '1';
  uint64_t curr_square = sq(currRank, currFile);
  uint64_t targ_square = sq(targRank, targFile);
  if (!validMove(board, curr_square, targ_square)) return;
  PieceInfo mover = getPieceType(board, curr_square);
  PieceInfo victim = getPieceType(board, targ_square);

  if (mover.type == NONE) return;

  if (victim.type != NONE) board.pieces[victim.color][victim.type] &= ~targ_square;

   board.pieces[mover.color][mover.type] &= ~curr_square;
   board.pieces[mover.color][mover.type] |= targ_square;
}
void clear() {
    std::cout <<  "\033[2J\033[H" << std::flush;
}

int main() {
  BoardState board;
  printBoard(board);
  
  int moveCount = 0;

  while (true) {
    ++moveCount;
    std::cout << (!(moveCount % 2 == 0) ? "Whites Move: " : "Blacks Move") << std::endl;
    std::string curr, targ;
    std::cin >> curr >> targ;
    move(curr, targ, board);
    clear();
    printBoard(board);
  }
}
