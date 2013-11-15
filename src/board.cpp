#include "board.h"
#include "piecegroup.h"

#include <algorithm>

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

void Board::resolve(Piece player, int x, int y) {
	vector<Point> black;
	vector<Point> white;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			Point p(i,j);
			if (at(i,j) == WHITE) {
				white.push_back(p);
			} else if (at(i,j) == BLACK) {
				black.push_back(p);
			}
		}
	}

	vector<PieceGroup> player1 = (player == WHITE ? groupify(black) : groupify(white));
	vector<PieceGroup> player2 = (player == WHITE ? groupify(white) : groupify(black));

	for (vector<PieceGroup>::iterator p1 = player1.begin(); p1 != player1.end(); ++p1) {
		set<Point, PointCmp> edges = (*p1).getEdges();
		for (set<Point, PointCmp>::iterator e = edges.begin(); e != edges.end(); ++e) {
			if (at(*e) != NONE) {
				set<Point, PointCmp> piecesToRemove = p1->pieces;
				for (set<Point, PointCmp>::iterator p = piecesToRemove.begin();
					p != piecesToRemove.end();
					++p) {
					curr[p->x][p->y] = NONE;
					return;
				}
			}
		}
	}
	
	for (vector<PieceGroup>::iterator p2 = player2.begin(); p2 != player2.end(); ++p2) {
		set<Point, PointCmp> edges = (*p2).getEdges();
		for (set<Point, PointCmp>::iterator e = edges.begin(); e != edges.end(); ++e) {
			if (at(*e) != NONE) {
				set<Point, PointCmp> piecesToRemove = p2->pieces;
				for (set<Point, PointCmp>::iterator p = piecesToRemove.begin();
					p != piecesToRemove.end();
					++p) {
					curr[p->x][p->y] = NONE;
					return;
				}
			}
		}
	}
}

vector<PieceGroup> Board::groupify(vector<Point> points) {
	vector<PieceGroup> groups;
	
	vector<Point>::iterator p = points.begin();
	while (p != points.end()) {
		PieceGroup g(this, at(*p), set<Point, PointCmp>());
		g.add(*p);
		for (set<Point>::iterator it = g.pieces.begin(); it != g.pieces.end(); ++it) {
			p = points.erase(remove(points.begin(), points.end(), *it), points.end());
		}
		groups.push_back(g);
	}

	return groups;
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
