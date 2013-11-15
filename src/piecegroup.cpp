#include "common.h"
#include "piecegroup.h"
#include "board.h"

using namespace std;

PieceGroup::PieceGroup(Board *b, const Piece c, set<Point, PointCmp> p) 
	: board(b), color(c), pieces(p) {}

void PieceGroup::add(const Point p) {
	if ((*board).at(p) != color) {
		return;
	}

	pieces.insert(p);
	vector<Point> n = (*board).getNeighbors(p);
	set<Point, PointCmp> edges(n.begin(), n.end());

	for (set<Point>::iterator it = edges.begin(); it != edges.end(); ++it) {
		if ((*board).at(*it) == color) {
			add(*it);
		}
	}
}

set<Point, PointCmp> PieceGroup::getEdges() {
	set<Point, PointCmp> edges;

	for (set<Point>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		vector<Point> neigh = (*board).getNeighbors(*it);
		for (vector<Point>::iterator n = neigh.begin(); n != neigh.end(); ++n) {
			if (pieces.find(*n) == pieces.end()) {
				edges.insert(*n);
			}
		}
	}

	return edges;
}
