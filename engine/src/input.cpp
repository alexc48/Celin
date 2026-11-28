#include <string>
#include <iostream>
#include <cstdlib>

#include "chess/input.hpp"
#include "chess/board.hpp"

void getMove(std::string& curr, std::string& targ, const BoardState& board) {
  std::cout << "Move #" << board.fullMoveCount<< '\n';
  std::cout << ((board.sideToMove == WHITE) ? "Whites Move: " : "Blacks Move: ") << std::endl;
  if (!(std::cin >> curr >> targ)) {
    std::exit(0); 
  }
}