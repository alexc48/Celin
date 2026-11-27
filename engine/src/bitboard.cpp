#include <iostream>
#include <bit>

#include "chess/types.hpp"

Bitboard sq(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}

int rank_of(Bitboard bb) {
  return std::countr_zero(bb) >> 3;
}

int file_of(Bitboard bb) {
  return std::countr_zero(bb) & 7;
}

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