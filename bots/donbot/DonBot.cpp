#include "GoBot.h"
#include "DonBot.h"
#include "src/board.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <climits>
#include <algorithm>

using namespace std;

int treeSize = 0;

DonBot::DonBot() {
	Row r(9,NONE);
	prev = Grid(BOARD_SIZE, r);
	last = Grid(BOARD_SIZE, r);
}

DonBot::~DonBot() {}
Grid DonBot::stateToGrid(int boardState[9][9]) {
	Row r(9,NONE);
	Grid grid(9,r);
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			grid[i][j] = static_cast<Piece>(boardState[i][j]);
		}
	}
	return grid;
}

void DonBot::onMyTurn(int boardState[9][9], int pnum, int &moveX,int &moveY , int &pass){
	mPlayerNumber = pnum;
	//cerr << "I am player number " << pnum << endl;
	//moveX = rand() % 9;
	//moveY = rand() % 9;
	//pass = 0;
	Grid curr = stateToGrid(boardState);

	Board * board = new Board(curr,prev,last);
	treeSize = 0;
	MoveNode node = minimax(board,3,true);
	moveX = node.x;
	moveY = node.y;
	pass = 0;
	cerr << "Minimax tree size: " << treeSize << ", Value: " << node.value << endl;
	
	//cerr << " making move " << moveY << " " << moveX << endl;

	//for ( int i = 0 ; i < 9 ; i++){
	//	for ( int j = 0 ; j < 9 ; j++){
	//		cerr << boardState[i][j] << " " ;
	//	}
	//	cerr << endl;
	//}
	last = prev;
	prev = curr;
}

list<Point> DonBot::getPossibleMoves(const Grid &state, int mPlayerNumber) {
	list<Point> mlist;

	int other = (mPlayerNumber==1)?2:1;

	for(int i = 1; i < 8; i++){
		for(int j = 1; j < 8; j++){
			//if((i == 0 || i == 8) && (j == 0 || j == 8)) {
			//	Point tmp(i,j);
			//	mlist.push_back(tmp);
			//} else if(state[i][j] == 0) {
				if((state[i-1][j] == other)
					|| (state[i][j-1] == other)
					|| (state[i+1][j] == other)
					|| (state[i][j+1] == other)) {
					Point tmp(i,j);
					mlist.push_back(tmp);
				}
			//}
		}
	}

	if(mlist.size() > 0)
		return mlist;
	
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(state[i][j] == 0) {
				Point tmp(i,j);
				mlist.push_back(tmp);
			}
		}
	}

	if(mlist.size() > 0)
		return mlist;
		
	mlist.push_back(Point(rand() % 9,rand() % 9));
	
	return mlist;
}

MoveNode DonBot::minimax(Board * board, int depth, bool isMaximizing) {
	//cerr << depth << endl;
	if(depth == 0) {
		treeSize++;
		MoveNode move;
		int winSum = 0;
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if(board->curr[i][j] == mPlayerNumber) {
					winSum++;
				} else if(board->curr[i][j] != 0) {
					winSum--;
				}
			}
		}
		move.value = winSum;
		return move;
	}

	//cerr << "here" << endl;

	if(isMaximizing) {
		//cerr << "maximizing" << endl;
		MoveNode bestMove;
		bestMove.x = -1;
		bestMove.y = -1;
		bestMove.value = INT_MIN;
		
		list<Point> moves = getPossibleMoves(board->curr,mPlayerNumber);

		// iterate over each move
		for(list<Point>::iterator it = moves.begin(); it != moves.end(); it++) {
			Board * nextState = 0;
			//cerr << it->x << ", " << it->y << endl;
			if(nextState = board->placeGet(it->x,it->y,static_cast<Piece>(mPlayerNumber))) {
				MoveNode child = minimax(nextState,depth-1,false);
				if(child.value > bestMove.value) {
					bestMove.x = it->x;
					bestMove.y = it->y;
					bestMove.value = child.value;
				}
			}
			if(nextState)
				delete nextState;
		}

		return bestMove;
	} else {
		int otherPlayer = (mPlayerNumber==1)?2:1;
		//cerr << "Other player: " << otherPlayer << endl;
		MoveNode bestMove;
		bestMove.x = -1;
		bestMove.y = -1;
		bestMove.value = INT_MAX;
		
		list<Point> moves = getPossibleMoves(board->curr,otherPlayer);

		// iterate over each move
		for(list<Point>::iterator it = moves.begin(); it != moves.end(); it++) {
			Board * nextState = 0;
			if(nextState = board->placeGet(it->x,it->y,static_cast<Piece>(otherPlayer))) {
				MoveNode child = minimax(nextState,depth-1,true);
				if(child.value < bestMove.value) {
					bestMove.x = it->x;
					bestMove.y = it->y;
					bestMove.value = child.value;
				}
			}
			if(nextState)
				delete nextState;
		}

		return bestMove;
	}
}

int main(){
	srand ((unsigned)time(0));
	DonBot * bot = new DonBot();
	bot->start();
}
