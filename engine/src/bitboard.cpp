
#include "chess/bitboard.hpp"

#include <iostream>

std::string bb_to_str(std::bitset<64> bb) {
  std::string flipped(64, '0');
  std::string bb_str = bb.to_string();
  size_t i = 0;
  for(int row = 0; row < 8; ++row) {
    for (int col = 7; col >= 0; --col) {
      flipped[i] = bb_str[static_cast<size_t>(row * 8 + col)];
      i++;
    }
  }
  return flipped;
}

void printBitboard(std::bitset<64> pieceBitboard) {
  std::string bb = bb_to_str(pieceBitboard);
  for (size_t i = 0; i < 64; ++i) { if ((i % 8 == 0) && i != 0) {
      std::cout << '\n';
    }
    std::cout << bb[i] << ' ';
  }
  std::cout << '\n';
}