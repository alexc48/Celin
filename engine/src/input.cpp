#include <string>
#include <iostream>

void getMove(std::string& curr, std::string& targ, const int& moveCount) {
  std::cout << "Move #" << moveCount << '\n';
  std::cout << (!(moveCount % 2 == 0) ? "Whites Move: " : "Blacks Move") << std::endl;
  std::cin >> curr >> targ;
}

bool blacksTurn(const int& moveCount) {
  return (moveCount % 2 == 0);
}
