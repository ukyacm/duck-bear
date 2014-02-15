#include "GoBot.h"
#include "ExampleBot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void ExampleBot::onMyTurn(int boardState[9][9], int iPlayerNum, int &iNext_X_Move,int &iNext_Y_Move , int &iP){

	//Your Turn Process goes here, decide where you want go with xPos , yPos
	
	iNext_X_Move = rand() % 9;
	iNext_Y_Move = rand() % 9;
	cerr << iNext_Y_Move << " " << " making move " << iNext_X_Move << endl;
	iP = rand() % 1;

	for ( int i = 0 ; i < 9 ; i++){
		for ( int j = 0 ; j < 9 ; j++){
			cerr << boardState[i][j] << " " ;
		}
		cerr << endl;
	}


	//setMyTurnMove(iNext_X_Move,iNext_Y_Move,iP);
}

int main(){
	srand ((unsigned)time(0));
	ExampleBot * bot = new ExampleBot();
	bot->start();
}
