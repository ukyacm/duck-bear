#include "GoBot.h"
#include "ExampleBot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void ExampleBot::onMyTurn(int boardState[][9], int iPlayerNum){
	int iNext_X_Move, iNext_Y_Move, iP;

	//Your Turn Process goes here, decide where you want go with xPos , yPos
	srand (time(NULL));
	iNext_X_Move = rand() % 9;
	iNext_Y_Move = rand() % 9;
	iP = rand() % 1;

	setMyTurnMove(iNext_X_Move,iNext_Y_Move,iP);
}

int main(){
	ExampleBot * bot = new ExampleBot();
	bot->start();
}
