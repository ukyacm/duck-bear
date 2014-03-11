#ifndef PIECEGROUP_H
#define PIECEGROUP_H

#include "common.h"

#include <set>
#include <vector>

class Board;

class PieceGroup {
	public:
	std::set<Point, PointCmp> pieces;
	
	PieceGroup(Board *b, const Piece c, std::set<Point, PointCmp> p);

	void add(const Point p, std::vector<Point> &points, std::vector<Point> &visited);
	std::set<Point, PointCmp> getEdges();
	Piece getColor() const;

	private:
	Board *board;
	Piece color;
};

#endif
