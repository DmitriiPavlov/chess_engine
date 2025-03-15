#include "board_representation.h"
#include <cstdint>

SlowBoardInterface::SlowBoardInterface(const BOARD_BITMASK& internal_bitmask): bitmask(internal_bitmask){};

SlowBoardInterface::SlowBoardInterface(){
	bitmask = {};
}

PIECE SlowBoardInterface::getPiece(int x, int y) const{
	uint64_t point_bitmask = uint64_t(1) << (y*ROW_WIDTH + x);

	if ((bitmask.WHITE_PAWN & point_bitmask) != 0){
		return PIECE::WHITE_PAWN; 
	}

	if ((bitmask.WHITE_KNIGHT & point_bitmask) != 0){
		return PIECE::WHITE_KNIGHT; 
	}

	if ((bitmask.WHITE_BISHOP & point_bitmask) != 0){
		return PIECE::WHITE_BISHOP; 
	}

	if ((bitmask.WHITE_ROOK & point_bitmask) != 0){
		return PIECE::WHITE_ROOK; 
	}

	if ((bitmask.WHITE_QUEEN & point_bitmask) != 0){
		return PIECE::WHITE_QUEEN; 
	}

	if ((bitmask.WHITE_KING & point_bitmask) != 0){
		return PIECE::WHITE_KING; 
	}


	if ((bitmask.BLACK_PAWN & point_bitmask) != 0){
		return PIECE::BLACK_PAWN; 
	}

	if ((bitmask.BLACK_KNIGHT & point_bitmask) != 0){
		return PIECE::BLACK_KNIGHT; 
	}

	if ((bitmask.BLACK_BISHOP & point_bitmask) != 0){
		return PIECE::BLACK_BISHOP; 
	}

	if ((bitmask.BLACK_ROOK & point_bitmask) != 0){
		return PIECE::BLACK_ROOK; 
	}

	if ((bitmask.BLACK_QUEEN & point_bitmask) != 0){
		return PIECE::BLACK_QUEEN; 
	}

	if ((bitmask.BLACK_KING & point_bitmask) != 0){
		return PIECE::BLACK_KING; 
	}

	return PIECE::EMPTY;
}

void SlowBoardInterface::setPiece(int x, int y, PIECE piece){
	uint64_t point_bitmask = uint64_t(1) << (y*ROW_WIDTH + x);

	switch(piece){
		case PIECE::WHITE_PAWN: 
		bitmask.WHITE_PAWN = bitmask.WHITE_PAWN | point_bitmask; 
		break;
		case PIECE::WHITE_KNIGHT:
		bitmask.WHITE_KNIGHT = bitmask.WHITE_KNIGHT | point_bitmask;
		break;
		case PIECE::WHITE_BISHOP:
		bitmask.WHITE_BISHOP = bitmask.WHITE_BISHOP | point_bitmask;
		break;
		case PIECE::WHITE_ROOK:
		bitmask.WHITE_ROOK = bitmask.WHITE_ROOK | point_bitmask;
		break;
		case PIECE::WHITE_QUEEN:
		bitmask.WHITE_QUEEN = bitmask.WHITE_QUEEN | point_bitmask;
		break;
		case PIECE::WHITE_KING:
		bitmask.WHITE_KING = bitmask.WHITE_KING | point_bitmask;
		break;
		case PIECE::BLACK_PAWN:
		bitmask.BLACK_PAWN = bitmask.BLACK_PAWN | point_bitmask;
		break;
		case PIECE::BLACK_KNIGHT:
		bitmask.BLACK_KNIGHT = bitmask.BLACK_KNIGHT | point_bitmask;
		break;
		case PIECE::BLACK_BISHOP:
		bitmask.BLACK_BISHOP = bitmask.BLACK_BISHOP | point_bitmask;
		break;
		case PIECE::BLACK_ROOK:
		bitmask.BLACK_ROOK = bitmask.BLACK_ROOK | point_bitmask;
		break;
		case PIECE::BLACK_QUEEN:
		bitmask.BLACK_QUEEN = bitmask.BLACK_QUEEN | point_bitmask;
		break;
		case PIECE::BLACK_KING:
		bitmask.BLACK_KING = bitmask.BLACK_KING | point_bitmask;
		break;
		default:
		break;
	}
}

