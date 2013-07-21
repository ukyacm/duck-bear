#include "board.h"

Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++ ) {
		Row r;
		curr.push_back(r);
	}
}
