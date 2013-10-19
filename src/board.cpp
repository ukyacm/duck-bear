#include "board.h"
#include "common.h"

using namespace std;

Board::Board() {
	Row r(BOARD_SIZE, NONE);
	Grid curr(BOARD_SIZE, r);
	Grid prev(BOARD_SIZE, r);
	Grid last(BOARD_SIZE, r);
}

bool Board::isOccupied(int x, int y) {
	return !curr[x][y];
}

void Board::place(int x, int y, Piece player) {
	if (!((0 <= x) && (x < BOARD_SIZE) && (0 <= y) && (y < BOARD_SIZE))) {
		throw new IllegalMoveException("POSITION OUT OF BOUNDS");
	}

	if (isOccupied(x,y)) {
		throw new IllegalMoveException("POSITION ALREADY FULL");
	}

	Grid temp = last;
	last = prev;
	prev = curr;

	curr[x][y] = player;
	resolve(player,x,y);

	if (curr == prev) {
		last = temp;
		prev = last;
		curr = prev;		
		throw new IllegalMoveException("RETURN TO PREVIOUS STATE");
	}
}

vector<Point> Board::getNeighbors(Point p) {
	vector<Point> points;
	if (p.x-1 >= 0) {points.push_back(Point(p.x-1,p.y));}
	if (p.x+1 < BOARD_SIZE) {points.push_back(Point(p.x+1,p.y));}
	if (p.y-1 >= 0) {points.push_back(Point(p.x,p.y-1));}
	if (p.y+1 < BOARD_SIZE) {points.push_back(Point(p.x,p.y+1));}
	return points;
}

vector<vector<Point> > Board::groupify(vector<Point> points) {
	vector<vector<Point> > group;

	for (vector<Point>::iterator p = points.begin(); p != points.end(); ++p) {
		vector<Point> nbrs = getNeighbors(*p);
		for (vector<Point>::iterator n = nbrs.begin(); n != nbrs.end(); ++n) {
			if (at(*p) == at(*n)) {
				
			}
		}
	}
}

void Board::resolve(Piece player, int x, int y) {
	vector<Point> black;
	vector<Point> white;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			Point p(i,j);
			if (at(i,j) == WHITE) {
				white.push_back(p);
			} else {
				black.push_back(p);
			}
		}
	}

	vector<vector<Point> > black_groups = groupify(black);
	vector<vector<Point> > white_groups = groupify(white);


}

Piece Board::at(const int x, const int y) const {
	return curr.at(x).at(y);
}

Piece Board::at(const Point p) const {
	return at(p.x,p.y);
}

string Board::toString() {
	ostringstream oss;

	for (vector<Row>::iterator r = curr.begin(); r != curr.end(); ++r) {
		for (vector<Piece>::iterator p = (*r).begin(); p != (*r).end(); ++p) {
			oss << (*p); 
		}
	}

	return oss.str();
}
