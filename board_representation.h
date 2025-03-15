#ifndef BOARD_REPRESENTATION_H
#define BOARD_REPRESENTATION_H

#include <cstdint>

#define ROW 0b11111111
#define ROW_WIDTH 8

typedef uint64_t BITMASK;

// until further notice, each of the below is stored as follows
// every byte is a row, so (0b_1111_1111 << 8*row_id) would give you the ith row
// (i.e. , the lsb holds row 0) within each byte, the least significant bit is
// col 0, so (0b_0000_0001 << col_id) could isolate a given bit from a row all
// of this put together, means that getting a singular point would be something
// like this: (BITMASK && (0b_0000_0001 << col_id << 8*row_id) >> col_id >>
// 8*row_id
typedef struct BOARD_BITMASK {
  BITMASK WHITE_PAWN = 0;
  BITMASK WHITE_KNIGHT = 0;
  BITMASK WHITE_BISHOP = 0;
  BITMASK WHITE_ROOK = 0;
  BITMASK WHITE_QUEEN = 0;
  BITMASK WHITE_KING = 0;
  BITMASK BLACK_PAWN = 0;
  BITMASK BLACK_KNIGHT = 0;
  BITMASK BLACK_BISHOP = 0;
  BITMASK BLACK_ROOK = 0;
  BITMASK BLACK_QUEEN = 0;
  BITMASK BLACK_KING = 0;
} BOARD_BITMASK;

enum class PIECE {
  WHITE_PAWN,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_ROOK,
  WHITE_QUEEN,
  WHITE_KING,
  BLACK_PAWN,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_ROOK,
  BLACK_QUEEN,
  BLACK_KING,
  EMPTY,
};

class SlowBoardInterface {
public:
  BOARD_BITMASK bitmask;

  SlowBoardInterface(const BOARD_BITMASK &internal_bitmask);
  SlowBoardInterface();

  // keep in mind, y is row_id and x is col_id
  PIECE getPiece(int x, int y) const;
  void setPiece(int x, int y, PIECE);
};

#endif
