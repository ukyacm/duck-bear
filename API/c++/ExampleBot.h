#ifndef EXAMPLEBOT_H
#define EXAMPLEBOT_H

#include "GoBot.h"

class GoBot;

class ExampleBot : public GoBot {
public:

	ExampleBot(){
	};

	~ExampleBot(){

	};

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
