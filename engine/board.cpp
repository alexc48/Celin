#include <iostream>
#include <bitset>
#include <string>
#include <cstdint>
#include <vector>

uint64_t sq(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}

struct BoardState {
  uint64_t white_pawn = (0xFFULL << 8);
  uint64_t black_pawn = (0xFFULL << 48);
  uint64_t white_knight = sq(0, 1) | sq(0, 6);
  uint64_t black_knight = sq(7, 1) | sq(7, 6);
  uint64_t white_bishop = sq(0,2) | sq(0, 5);
  uint64_t black_bishop = sq(7,2) | sq(7, 5);
  uint64_t white_rook = sq(0,0) | sq(0,7);
  uint64_t black_rook = sq(7, 0) | sq(7, 7);
  uint64_t white_queen = sq(0, 3);
  uint64_t black_queen = sq(7, 3);
  uint64_t white_king = sq(0, 4);
  uint64_t black_king = sq(7, 4);

};

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
  for (int i = 0; i < 64; ++i) {
    if ((i % 8 == 0) && i != 0) {
      std::cout << '\n';
    }
    std::cout << bb[i] << ' ';
  }
  std::cout << '\n';
}

void printBoard(BoardState board) {
  std::string board_str[64];

  std::string white_pawn_str = bb_to_str(board.white_pawn);
  std::string white_knight_str = bb_to_str(board.white_knight);
  std::string white_bishop_str = bb_to_str(board.white_bishop);
  std::string white_rook_str = bb_to_str(board.white_rook);
  std::string white_queen_str = bb_to_str(board.white_queen);
  std::string white_king_str = bb_to_str(board.white_king);

  std::string black_pawn_str = bb_to_str(board.black_pawn);
  std::string black_knight_str = bb_to_str(board.black_knight);
  std::string black_bishop_str = bb_to_str(board.black_bishop);
  std::string black_rook_str = bb_to_str(board.black_rook);
  std::string black_queen_str = bb_to_str(board.black_queen);
  std::string black_king_str = bb_to_str(board.black_king);


  for (int i = 0; i < 64; ++i) {
    if      (white_pawn_str[i] == '1')   board_str[i] = "♙";
    else if (white_knight_str[i] == '1') board_str[i] = "♘";
    else if (white_bishop_str[i] == '1') board_str[i] = "♗";
    else if (white_rook_str[i] == '1')   board_str[i] = "♖";
    else if (white_queen_str[i] == '1')  board_str[i] = "♕";
    else if (white_king_str[i] == '1')   board_str[i] = "♔";

    else if (black_pawn_str[i] == '1')   board_str[i] = "♟";
    else if (black_knight_str[i] == '1') board_str[i] = "♞";
    else if (black_bishop_str[i] == '1') board_str[i] = "♝";
    else if (black_rook_str[i] == '1')   board_str[i] = "♜";
    else if (black_queen_str[i] == '1')  board_str[i] = "♛";
    else if (black_king_str[i] == '1')   board_str[i] = "♚";

    else     board_str[i] = "·";
  }

  for (int i = 0; i < 64; ++i) {
    if (i % 8 == 0) {
      std::cout << '\n';
    }
    std::cout << board_str[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  BoardState board;
  //printBoard(board);
}
