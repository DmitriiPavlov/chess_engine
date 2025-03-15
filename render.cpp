#include "render.h"

// evil macros to print text easily
#define RED(text) std::cout << "\033[31m" << text << "\033[0m"
#define WHITE(text) std::cout << "\033[37m" << text << "\033[0m"
#define BLUE(text) std::cout << "\033[34m" << text << "\033[0m"

// WHITE will be in RED Text and BLACK will be in BLUE Text
void printBoard(BOARD_BITMASK board) {
  SlowBoardInterface interface = SlowBoardInterface(board);
  for (int y = 7; y >= 0; y--) {
    for (int x = 0; x < 8; x++) {
      PIECE piece = interface.getPiece(x, y);
      printPiece(piece);
      std::cout<<" ";
    }
    std::cout<<"\n";
  }
}

void printPiece(PIECE piece){
    switch(piece) { 
      case PIECE::WHITE_PAWN:
        RED("p");
        break;
      case PIECE::WHITE_KNIGHT:
        RED("N");
        break;
      case PIECE::WHITE_BISHOP:
        RED("B");
        break;
      case PIECE::WHITE_ROOK:
        RED("R");
        break;
      case PIECE::WHITE_QUEEN:
        RED("Q");
        break;
      case PIECE::WHITE_KING:
        RED("K");
        break;

      case PIECE::BLACK_PAWN:
        BLUE("p");
        break;
      case PIECE::BLACK_KNIGHT:
        BLUE("N");
        break;
      case PIECE::BLACK_BISHOP:
        BLUE("B");
        break;
      case PIECE::BLACK_ROOK:
        BLUE("R");
        break;
      case PIECE::BLACK_QUEEN:
        BLUE("Q");
        break;
      case PIECE::BLACK_KING:
        BLUE("K");
        break;

      default:
        WHITE("·");
        break;
      }
}
