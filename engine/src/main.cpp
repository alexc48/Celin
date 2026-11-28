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

  while (true) {
    std::string curr, targ;
    Bitboard curr_square = 0;
    Bitboard targ_square = 0;

    std::string error;

    getMove(curr, targ, board);
    while (!validMove(board, curr, targ, curr_square, targ_square, error)) {
      clear();
      printBoard(board);
      std::cout << error << '\n';
      getMove(curr, targ, board);
    }

    move(board, curr_square, targ_square);
    
    clear();
    printBoard(board);
  }
}