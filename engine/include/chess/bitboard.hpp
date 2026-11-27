#pragma once

#include <bitset>
#include "chess/types.hpp"

Bitboard sq(int rank, int file);

int rank_of(Bitboard bb);

int file_of(Bitboard bb);

std::string bb_to_str(std::bitset<64> bb);

void printBitboard(std::bitset<64> pieceBitboard);