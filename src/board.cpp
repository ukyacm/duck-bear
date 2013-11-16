#include "board.h"
#include "piecegroup.h"

#include <algorithm>
#include <iostream>

using namespace std;

Board::Board() {
	Row r(BOARD_SIZE, NONE);
	curr = Grid(BOARD_SIZE, r);
	prev = Grid(BOARD_SIZE, r);
	last = Grid(BOARD_SIZE, r);
}

bool Board::isOccupied(int x, int y) {
	return (curr[x][y] != NONE);
}

void Board::place(int x, int y, Piece player) {	
	if (!((0 <= x) && (x < BOARD_SIZE) && (0 <= y) && (y < BOARD_SIZE))) {
		throw IllegalMoveException("POSITION OUT OF BOUNDS");
	}
	
	if (isOccupied(x,y)) {
		throw IllegalMoveException("POSITION ALREADY FULL");
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
		throw IllegalMoveException("RETURN TO PREVIOUS STATE");
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
	
	vector<PieceGroup> player1, player2;
	Piece player1color, player2color;
	if (player == WHITE) {
		player1 = groupify(white);
		player1color = WHITE;
		player2 = groupify(black);
		player2color = BLACK;
	} else {
		player1 = groupify(black);
		player1color = BLACK;
		player2 = groupify(white);
		player2color = WHITE;
	}

	// for each group belonging to player 1
	for (vector<PieceGroup>::iterator p2 = player2.begin(); p2 != player2.end(); ++p2) {
		// get the list of edge pieces
		set<Point, PointCmp> edges = (*p2).getEdges();
		
		// assume it is surrounded
		bool surrounded = true;
		
		// find a piece that proves otherwise
		for (set<Point, PointCmp>::iterator e = edges.begin(); e != edges.end(); ++e) {
			Piece pointColor = at(*e);
			if (pointColor != player1color) {
				surrounded = false;
				break;
			}
		}
		
		// remove surrounded pieces; i.e. this group
		if(surrounded) {
			set<Point, PointCmp> piecesToRemove = p2->pieces;
			for (set<Point, PointCmp>::iterator p = piecesToRemove.begin();
				p != piecesToRemove.end();
				++p) {
				curr[p->x][p->y] = NONE;
			}
		}
	}

	// for each group belonging to player 1
	for (vector<PieceGroup>::iterator p1 = player1.begin(); p1 != player1.end(); ++p1) {
		// get the list of edge pieces
		set<Point, PointCmp> edges = (*p1).getEdges();
		
		// assume it is surrounded
		bool surrounded = true;
		
		// find a piece that proves otherwise
		for (set<Point, PointCmp>::iterator e = edges.begin(); e != edges.end(); ++e) {
			Piece pointColor = at(*e);
			if (pointColor != player2color) {
				surrounded = false;
				break;
			}
		}
		
		// remove surrounded pieces; i.e. this group
		if(surrounded) {
			set<Point, PointCmp> piecesToRemove = p1->pieces;
			for (set<Point, PointCmp>::iterator p = piecesToRemove.begin();
				p != piecesToRemove.end();
				++p) {
				curr[p->x][p->y] = NONE;
			}
		}
	}
}

vector<PieceGroup> Board::groupify(vector<Point> points) {
	vector<PieceGroup> groups;
	
	while (!points.empty()) {
		Point p = points.back();
		points.pop_back();
		PieceGroup g(this, at(p), set<Point, PointCmp>());
		vector<Point> visited;
		g.add(p,points,visited);
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

string Board::preview() {
	ostringstream oss;

	for (vector<Row>::iterator r = curr.begin(); r != curr.end(); ++r) {
		for (vector<Piece>::iterator p = (*r).begin(); p != (*r).end(); ++p) {
			oss << (*p) << " "; 
		}
		oss << endl;
	}

	return oss.str();
}
