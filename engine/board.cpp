#include <iostream>
#include <bitset>
#include <string>
#include <cstdint>

uint64_t sq(int rank, int file) {
    uint64_t square = 1ULL;
    square = square << (rank * 8 + file);
    return square;
}

void printBitboard(std::bitset<64> pieceBitboard, std::string pieceIcon) {
  std::string bb = pieceBitboard.to_string();
  for (int row = 0; row < 8; ++row) {
    for (int col = 7; col >= 0; --col) {
      if (bb[row * 8 + col] == '1') {
        std::cout << pieceIcon << ' ';
      } else {
        std::cout << "·" << ' ';
      }
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

struct BoardState {
  uint64_t white_pawn =
  (0b11111111ULL << ((2 * 8) - 8));

  uint64_t black_pawn =
  (0b11111111ULL << ((7 * 8) - 8));

  uint64_t white_knight =
  sq(0, 1) + sq(0, 6);

  uint64_t black_knight = 
  sq(7, 1) + sq(7, 6);

  uint64_t white_bishop =
  sq(0,2) + sq(0, 5);

  uint64_t black_bishop =
  sq(7,2) + sq(7, 5);

  uint64_t white_rook = 
  sq(0,0) + sq(0,7);

  uint64_t black_rook = 
  sq(7, 0) + sq(7, 7);

  uint64_t white_queen =
  sq(0, 3);

  uint64_t black_queen = 
  sq(7, 3);

  uint64_t white_king = 
  sq(0, 4);

  uint64_t black_king =
  sq(7, 4);

};

int main() {
  BoardState board;
}
