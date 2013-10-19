#include "board.h"

Board::Board() {
	Row r(BOARD_SIZE, NONE);
	Grid curr(BOARD_SIZE, r);
	Grid prev(BOARD_SIZE, r);
	Grid last(BOARD_SIZE, r);
}

void Board::place(int x, int y, Piece player) {
	if (!((0 <= x) && (x < BOARD_SIZE) && (0 <= y) && (y < BOARD_SIZE))) {
		throw new IllegalMoveException("POSITION OUT OF BOUNDS")
	}

	if (!curr[x][y]) {
		throw new IllegalMoveException("POSITION ALREADY FULL");
	}

	Grid temp = last;
	last = prev;
	prev = curr;

	curr[x][y] = player;
	resolve(player);

	if (curr == prev) {
		last = temp;
		prev = last;
		curr = prev;		
		throw new IllegalMoveException("RETURN TO PREVIOUS STATE");
	}
}

void Piece::resolve(Player player) {
	// check first if player would capture
	// check by flling
	
	for (int i = 0; i < curr.length(); i++) {
		for (int j = 0; j < curr[i].length(); j++) {
			
		}
	}
}

Piece Board::at(int x, int y) {
	return curr.at(x).at(y);
}
