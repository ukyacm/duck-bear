#ifndef PIECEGROUP_H
#define PIECEGROUP_H

#include "common.h"

#include <set>

class Board;

class PieceGroup {
	public:
	std::set<Point, PointCmp> pieces;
	
	PieceGroup(Board *b, const Piece c, std::set<Point, PointCmp> p);

	void add(const Point p);
	std::set<Point, PointCmp> getEdges();
	Piece getColor() const;

	private:
	Board *board;
	Piece color;
};

#endif
