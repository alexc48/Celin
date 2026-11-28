#include <string>

#include "types.hpp"
#include "board.hpp"

bool validMove(const BoardState& board, const std::string& curr, const std::string& targ, Bitboard& curr_square, Bitboard& targ_square, const int& moveCount, std::string& error);