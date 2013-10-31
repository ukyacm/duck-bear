#ifndef UKACMGOAPI_H
#define UKACMGOAPI_H

#include "UKACMBotMsgHandler.h"

class UKACMBotMsgHandler;
class UKACMGoAPI;


class UKACMGoAPI : public UKACMBotMsgHandler{
public:

	UKACMGoAPI(){
	};

	~UKACMGoAPI(){

	};

	//implement onMyTurn to interact with the API, this is the main loop
	//Function parameters:
	//
	//BoardState: a 9x9 int array which would be BoardState[9][9]
	//
	//iPLayerNum: a int value indicating indicate white or black 
	//			  stone your bot plays
	void onMyTurn(int BoardState[][9], int iPlayerNum );
};

#endif