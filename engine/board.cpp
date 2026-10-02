#include <iostream>
#include <bitset>
#include <string>
#include <cstdint>
#include <vector>

// Bit board layout:
//a1 = bit 0, h1 = bit 7, a8 = bit 56, h8 = bit 63

enum Color     {WHITE, BLACK};
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

uint64_t sq(int rank, int file) {
    return 1ULL << (rank * 8 + file);
}

struct BoardState {
  // piece[color][type] -> bitboard
  uint64_t pieces[2][6] = {};

  BoardState() {
    pieces[WHITE][PAWN] = 0xFFULL << 8;
    pieces[BLACK][PAWN] = 0xFFULL << 48;
    pieces[WHITE][KNIGHT] = sq(0, 1) | sq(0, 6);
    pieces[BLACK][KNIGHT] = sq(7, 1) | sq(7, 6);
    pieces[WHITE][BISHOP] = sq(0,2) | sq(0, 5);
    pieces[BLACK][BISHOP] = sq(7,2) | sq(7, 5);
    pieces[WHITE][ROOK] = sq(0,0) | sq(0,7);
    pieces[BLACK][ROOK] = sq(7, 0) | sq(7, 7);
    pieces[WHITE][QUEEN] = sq(0, 3);
    pieces[BLACK][QUEEN] = sq(7, 3);
    pieces[WHITE][KING] = sq(0, 4);
    pieces[BLACK][KING] = sq(7, 4);
  }
};

std::string getPieceType(BoardState board, uint64_t bit) {

  uint64_t matching_mask; 
  matching_mask = (board.pieces[WHITE][PAWN] & bit);
  if (matching_mask > 0) return "Wpawn";
  matching_mask = (board.pieces[WHITE][KNIGHT] & bit);
  if (matching_mask > 0) return "Wknight";
  matching_mask = (board.pieces[WHITE][BISHOP] & bit);
  if (matching_mask > 0) return "Wbishop";
  matching_mask = (board.pieces[WHITE][ROOK] & bit);
  if (matching_mask > 0) return "Wrook";
  matching_mask = (board.pieces[WHITE][QUEEN] & bit);
  if (matching_mask > 0) return "Wqueen";
  matching_mask = (board.pieces[WHITE][KING] & bit);
  if (matching_mask > 0) return "Wking";

  return "N/A";
}

// turns bitboard into a correctly oriented board string
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
  for (int i = 0; i < 64; ++i) {
    if ((i % 8 == 0) && i != 0) {
      std::cout << '\n';
    }
    std::cout << bb[i] << ' ';
  }
  std::cout << '\n';
}

void printBoard(BoardState board) {
  std::string board_str[64];

  std::string white_pawn_str = bb_to_str(board.pieces[WHITE][PAWN]);
  std::string white_knight_str = bb_to_str(board.pieces[WHITE][KNIGHT]);
  std::string white_bishop_str = bb_to_str(board.pieces[WHITE][BISHOP]);
  std::string white_rook_str = bb_to_str(board.pieces[WHITE][ROOK]);
  std::string white_queen_str = bb_to_str(board.pieces[WHITE][QUEEN]);
  std::string white_king_str = bb_to_str(board.pieces[WHITE][KING]);

  std::string black_pawn_str = bb_to_str(board.pieces[BLACK][PAWN]);
  std::string black_knight_str = bb_to_str(board.pieces[BLACK][KNIGHT]);
  std::string black_bishop_str = bb_to_str(board.pieces[BLACK][BISHOP]);
  std::string black_rook_str = bb_to_str(board.pieces[BLACK][ROOK]);
  std::string black_queen_str = bb_to_str(board.pieces[BLACK][QUEEN]);
  std::string black_king_str = bb_to_str(board.pieces[BLACK][KING]);


  for (int i = 0; i < 64; ++i) {
    if      (white_pawn_str[i] == '1')   board_str[i] = "♙";
    else if (white_knight_str[i] == '1') board_str[i] = "♘";
    else if (white_bishop_str[i] == '1') board_str[i] = "♗";
    else if (white_rook_str[i] == '1')   board_str[i] = "♖";
    else if (white_queen_str[i] == '1')  board_str[i] = "♕";
    else if (white_king_str[i] == '1')   board_str[i] = "♔";

    else if (black_pawn_str[i] == '1')   board_str[i] = "♟";
    else if (black_knight_str[i] == '1') board_str[i] = "♞";
    else if (black_bishop_str[i] == '1') board_str[i] = "♝";
    else if (black_rook_str[i] == '1')   board_str[i] = "♜";
    else if (black_queen_str[i] == '1')  board_str[i] = "♛";
    else if (black_king_str[i] == '1')   board_str[i] = "♚";

    else     board_str[i] = "·";
  }

  for (int i = 0; i < 64; ++i) {
    if (i % 8 == 0) {
      std::cout << '\n';
    }
    std::cout << board_str[i] << ' ';
  }
  std::cout << '\n';
}

bool validateMove(const BoardState& board, const uint64_t curr_square, const uint64_t targ_square) {
  return true;
}
void move(const std::string& curr, const std::string& targ, BoardState& board) {
  int currFile = curr[0] - 'a';
  int currRank = curr[1] - '1';
  int targFile = targ[0] - 'a';
  int targRank = targ[1] - '1';
  uint64_t curr_square = sq(currRank, currFile);
  uint64_t targ_square = sq(targRank, targFile);
  if (validateMove(board, curr_square, targ_square)) {
    std::string currPieceType = getPieceType(board, curr_square);
    std::string targPieceType = getPieceType(board, targ_square);
    if (currPieceType == "Wpawn") {
      std::cout << "curr piece: " << currPieceType << '\n';
      // flip the white pawn bitboard bit at currSquare and targ_square

    }
  }
}

int main() {
  BoardState board;
  printBoard(board);

  while (true) {
    std::cout << "White move: ";
    std::string curr;
    std::string targ;
    std::cin >> curr >> targ;
    move(curr, targ, board);
  }
}
