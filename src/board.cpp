#include "board.h"

Board::Board() {
	Row r(BOARD_SIZE, NONE);
	Grid curr(BOARD_SIZE, r);
	Grid prev(BOARD_SIZE, r);
	Grid prever(BOARD_SIZE, r);
}

void Board::place(int x, int y, Piece player) {
	if (!((0 <= x) && (x < BOARD_SIZE) && (0 <= y) && (y < BOARD_SIZE))) {
		throw new IllegalMoveException("POSITION OUT OF BOUNDS")
	}

	if (!curr[x][y]) {
		throw new IllegalMoveException("POSITION ALREADY FULL");
	}

	curr[x][y] = player;
	resolve();

	if (curr == prev) {
		
		throw new IllegalMoveException("RETURN TO PREVIOUS STATE");
	}
}

Piece Board::at(int x, int y) {
	return curr.at(x).at(y);
}
