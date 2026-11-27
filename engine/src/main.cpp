#include <iostream>
#include <bitset>
#include <string>

#include "chess/types.hpp"
#include "chess/bitboard.hpp"
#include "chess/display.hpp"
#include "chess/input.hpp"
#include "chess/board.hpp"
#include "chess/movegen.hpp"

int main() {

  initDisplay(); 
  clear();
  BoardState board;
  printBoard(board);
  int moveCount = 0;

  while (true) {
    ++moveCount;
    std::string curr, targ;
    Bitboard curr_square = -1;
    Bitboard targ_square = -1;

    getMove(curr, targ, moveCount);
    while (!validMove(board, curr, targ, curr_square, targ_square, moveCount)) {
      getMove(curr, targ, moveCount);
    }

    move(board, curr_square, targ_square, moveCount);
    
    clear();
    printBoard(board);
  }
}