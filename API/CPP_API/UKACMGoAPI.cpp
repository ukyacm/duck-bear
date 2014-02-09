#include "UKACMBotMsgHandler.h"
#include "UKACMGoAPI.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void UKACMGoAPI::onMyTurn(int boardState[][9], int iPlayerNum){
	int iNext_X_Move, iNext_Y_Move, iP;

	//Your Turn Process goes here, decide where you want go with xPos , yPos
	srand (time(NULL));
	iNext_X_Move = rand() % 9;
	iNext_Y_Move = rand() % 9;
	iP = rand() % 1;

	setMyTurnMove(iNext_X_Move,iNext_Y_Move,iP);
}
