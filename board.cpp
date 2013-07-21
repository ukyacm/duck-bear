#include "board.h"

Board::Board() {
//	Board::curr = Grid(BOARD_SIZE, Row(BOARD_SIZE, Piece.NONE));
//	Board::prev = Grid(BOARD_SIZE, Row(BOARD_SIZE, Piece.NONE));
//	Board::prever = Grid(BOARD_SIZE, Row(BOARD_SIZE, Piece.NONE));

	for (int i = 0; i < BOARD_SIZE; i++ ) {
		Row r;
		curr.push_back(r);
	}
}
