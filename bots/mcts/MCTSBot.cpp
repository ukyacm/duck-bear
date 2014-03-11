#include "GoBot.h"
#include "MCTSBot.h"

#include "common.h"
#include "board.h"
#include "piecegroup.h"

#include "Node.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_iter = 10;

bool comp(Node* i, Node* j) {
	return i->UCT() > j->UCT();
}

void MCTSBot::onMyTurn(int boardState[9][9], int iPlayerNum, int &iNext_X_Move,int &iNext_Y_Move , int &iP){
	// rebuilding the board state. this will be the node from which we will do our search.
	Board board;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			board.curr[i][j] = Piece(boardState[i][j]);
		}
	}

	Node root(Point(-1,-1), NULL, board);
	vector<Node*> nodes;
	nodes.push_back(&root);

	for (int i = 0; i < 3; i++) {
		Node* curr = nodes.back();
		nodes.pop_back();

		cerr << "expanding...";
		curr->expand();
		cerr << "exploring...";
		int s = curr->children.size();
		for (vector<Node>::iterator node = curr->children.begin(); node != curr->children.end(); node++) {
			(*node).explore(85-s, 150);
			nodes.push_back(&(*node));
		}
		cerr << "sorting...";
		sort(nodes.begin(), nodes.end(), comp);
		cerr << nodes.size() << " nodes, rank " << nodes.back()->UCT() << endl;;
	}

	int dep = 0;
	Node* curr = nodes.back();
	while (curr->parent->parent != NULL) {
		curr = curr->parent;
		dep++;
	}

	cerr << "best at depth " << dep << " " << curr->move.x << ", " << curr->move.y << endl;

	iNext_X_Move = curr->move.x;
	iNext_Y_Move = curr->move.y;
	iP = false;
}

int main(){
	srand ((unsigned)time(0));
	MCTSBot * bot = new MCTSBot();
	bot->start();
}
