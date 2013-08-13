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
	std::string error;
	IllegalMoveException(const std::string e);
	const char * what();
};

class Board {
	public:
	static const int BOARD_SIZE = 9;

	Grid curr, prev, prever;
	
	Board();

	void place(const int x, const int y, const Piece p);
	Piece at(const int x, const int y) const;

	void resolve();
};

#endif
