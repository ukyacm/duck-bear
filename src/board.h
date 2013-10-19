#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <sstream>
#include <exception>

enum Piece {
	NONE,
	WHITE,
	BLACK
};

struct Point {
	int x;
	int y;

	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
};

typedef std::vector<Piece> Row;
typedef std::vector<Row> Grid;

class Board {
	public:
	static const int BOARD_SIZE = 9;

	Grid curr, prev, last;
	
	Board();

	void place(const int x, const int y, const Piece p);
	Piece at(const int x, const int y) const;
	Piece at(const Point p) const;
	
	std::string toString();

	private:
	std::vector<Piece> getNeighbors(Point p);
	void resolve(Piece player, int x, int y);
};

#endif
