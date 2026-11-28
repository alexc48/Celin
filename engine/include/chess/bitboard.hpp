#pragma once

#include "chess/types.hpp"
#include <bitset>
#include <bit>
#include <string>

constexpr Bitboard index2bitboard(u8 index) {
  return 1ULL << index;
}
constexpr Bitboard sq_bb(int rank, int file) {
    return index2bitboard(static_cast<u8>(rank * 8 + file)); 
}

constexpr u8 sq(int rank, int file) {
  return static_cast<u8>(rank * 8 + file);
}

constexpr int rank_of_bb(Bitboard bb) {
  return std::countr_zero(bb) >> 3;
}

constexpr int file_of_bb(Bitboard bb) {
  return std::countr_zero(bb) & 7;
}

constexpr int rank_of(u8 index) {
  return index >> 3;
}

constexpr int file_of(u8 index) {
  return index & 7;
}

std::string bb_to_str(std::bitset<64> bb);

void printBitboard(std::bitset<64> pieceBitboard);