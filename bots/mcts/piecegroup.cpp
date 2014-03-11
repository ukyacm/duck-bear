#include "common.h"
#include "piecegroup.h"
#include "board.h"
#include <algorithm>

#include <iostream>

using namespace std;

PieceGroup::PieceGroup(Board *b, const Piece c, set<Point, PointCmp> p) 
	: board(b), color(c), pieces(p) {}

Piece PieceGroup::getColor() const {
	return color;
}

void PieceGroup::add(const Point p, vector<Point> &points, vector<Point> &visited) {
	bool touched = (find(visited.begin(),visited.end(),p) != visited.end());
	if(touched || (*board).at(p) != color) 
		return;
		
	visited.push_back(p);

	pieces.insert(p);
	points.erase(remove(points.begin(), points.end(), p), points.end());
	
	vector<Point> n = (*board).getNeighbors(p);
	set<Point, PointCmp> edges(n.begin(), n.end());

	for (set<Point>::iterator it = edges.begin(); it != edges.end(); ++it) {
		add(*it,points,visited);
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
	
	// subtract inner pieces from edges
	for (set<Point>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		edges.erase(*it);
	}

	return edges;
}
