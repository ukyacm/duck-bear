#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>


enum Piece {
	NONE,
	WHITE,
	BLACK
};

typedef std::vector<Piece> Row;
typedef std::vector<Row> Grid;

class IllegalMoveException : public std::exception {
	public:
	string error;
	IllegalMoveException(const string e);
	const char * what();
};

class Board {
	public:
	const int BOARD_SIZE = 9;

	Grid curr, prev, prever;
	
	Board();
	~Board();

	void place(const int x, const int y);
	Piece at(const int x, const int y) const;

	void resolve();
};

#endif
