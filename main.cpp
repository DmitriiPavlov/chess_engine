//internal
#include "board_representation.h"
#include "render.h"


int main(){
	SlowBoardInterface board = SlowBoardInterface();
	printBoard(board.bitmask);
	std::cout<<"\n";
	board.setPiece(0,0,PIECE::WHITE_KNIGHT);
	board.setPiece(1,3,PIECE::BLACK_KING);
	printBoard(board.bitmask);
	
	return 0;
}
