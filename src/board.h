#ifndef BOARD_H
#define BOARD_H

#include "common.h"

#include <vector>
#include <string>
#include <sstream>
#include <exception>

typedef std::vector<Piece> Row;
typedef std::vector<Row> Grid;

class PieceGroup;

class Board {
	public:
	Grid curr, prev, last;
	
	Board();

	void place(const int x, const int y, const Piece p);
	Piece at(const int x, const int y) const;
	Piece at(const Point p) const;
	bool isOccupied(int x, int y);

	std::vector<Point> getNeighbors(Point p);

	std::string toString();

	private:
	std::vector<std::vector<Point> > groupify(std::vector<Point> points);
	void resolve(Piece player, int x, int y);
};

#endif
