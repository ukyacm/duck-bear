#ifndef NODE_H
#define NODE_H

#include <vector>

#include "board.h"
#include "common.h"

class Node {
	public:
	Board state;
	Point move;
	Node* parent;
	std::vector<Node> children;
	int wins;
	int visits;
	std::vector<Point> untried;
	Piece player;
	Piece last;

	Node(Point move, Node* parent, Board state);

	void expand();
	void explore(int num_games, int max_moves);
	double UCT();
};

#endif
