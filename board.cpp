#include "board.h"

Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++ ) {
		Row r;
		curr.push_back(r);
	}
}

Piece Board::at(int x, int y) {
	return curr.at(x).at(y);
}

void Board::place(int x, int y, Piece p) {
	


}
