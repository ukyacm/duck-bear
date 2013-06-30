#ifndef BOARD_H
#define BOARD_H

#include <string>

enum Piece {
	NONE,
	WHITE,
	BLACK
};

class IllegalMoveException : public std::exception {
	public:
	string error;
	IllegalMoveException(const string e);
	const char * what();
};

class Board {
	public:
	Piece board[9][9];
	
	Board();
	~Board();

	void place(const int x, const int y);
	Piece at(const int x, const int y) const;
};

#endif
