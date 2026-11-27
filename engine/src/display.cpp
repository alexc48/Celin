#include <iostream>
#include <string>

#include "chess/board.hpp"
#include "chess/types.hpp"
#include "chess/bitboard.hpp"



#ifdef _WIN32
#include <windows.h>
#endif


const std::string SYMBOLS[2][6] = {
  {"♙", "♘", "♗", "♖", "♕", "♔"},  // white
  {"♟", "♞", "♝", "♜", "♛", "♚"}   // black
};


void initDisplay() {
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
  #endif
}

void clear() {
    std::cout <<  "\033[2J\033[H" << std::flush;
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