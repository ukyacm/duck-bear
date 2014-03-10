#ifndef EXAMPLEBOT_H
#define EXAMPLEBOT_H

#include "GoBot.h"
#include "src/board.h"
#include "src/common.h"
#include <list>

class GoBot;

struct MoveNode {
	int x, y, value;
};

class DonBot : public GoBot {
public:
	DonBot();
	~DonBot();

	int mPlayerNumber;

	MoveNode minimax(Board * board, int depth, int alpha, int beta, bool isMaximizing);
	list<Point> getPossibleMoves(const Grid &state, int mPlayerNumber);
	vector<Point> getNeighbors(Point p);
	Grid stateToGrid(int boardState[9][9]);
	Point bad;

	Grid prev;
	Grid last;
	
	//implement onMyTurn to interact with the API, this is the main loop
	//Function parameters:
	//
	//BoardState: a 9x9 int array which would be BoardState[9][9]
	//
	//iPLayerNum: a int value indicating indicate white or black 
	//			  stone your bot plays
	void onMyTurn(int boardState[9][9], int iPlayerNum, int &iNext_X_Move,int &iNext_Y_Move , int &iP);
};

#endif
