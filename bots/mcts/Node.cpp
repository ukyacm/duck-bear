#include "Node.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "board.h"
#include "common.h"

using namespace std;


Node::Node(Point move, Node* parent, Board state) {
	this->move = Point(move);
	this->parent = parent;
	this->state = Board(state);
	vector<Node> children;
	wins = 0;
	visits = 0;
	untried = state.getMoves();
	player = last = state.lastPlayer;
}

void Node::expand() {
	while (!untried.empty()) {
		Board board(state);
		Point m(untried.back());
		try {
			board.place(m.x, m.y, player);
		} catch(...) {
			untried.pop_back();
			continue;
		}
		Node node(m, this, board);
		children.push_back(node);
		untried.pop_back();
	}
}

void Node::explore(int num_games, int max_moves) {
	for (int  i = 0; i < num_games; i++) {
		Board board(state);
		for (int j = 0; j < max_moves; j++) {
			vector<Point> moves = board.getMoves();
			if (moves.size() == 0) {
				break;
			}
			int p = rand() % moves.size();
			Point m = moves[p];
			last = Piece(3 - board.lastPlayer);
			try {
				board.place(m.x, m.y, player);
			} catch(...) {
				break;
			}
		}

		int white = 0;
		int black = 0;
		for (int l = 0; l < 9; l++) {
			for (int w = 0; w < 9; w++) {
				if (board.at(l,w) == WHITE) {white++;}
				if (board.at(l,w) == BLACK) {black++;}
			}
		}
		if (player == WHITE && white > black) {wins++;}
		if (player == BLACK && black > white) {wins++;}
		visits++;	
	}
	Node* prt = parent;
	while (prt != NULL) {
		(*prt).visits += visits;
		(*prt).wins += wins;
		prt = (*prt).parent;
	}
}

double Node::UCT() {
	Node* prt = parent;
	while (prt != NULL) {
		if ((*prt).parent == NULL) {
			break;
		}
		prt = (*prt).parent;
	}
	return double(wins) / double(visits) + sqrt(2.0 * ( log((*prt).visits) / visits));
}
