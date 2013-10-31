#ifndef UKACMBotMsgHandler_H
#define UKACMBotMsgHandler_H

//#include "UKACMGoAPI.h"

#include <vector>
#include <iostream>
#include <string>


using namespace std;

class UKACMBotMsgHandler{

private:
	static const int m_iBoard_Row = 9;
	static const int m_iBoard_Col = 9;
	int m_Board[m_iBoard_Row][m_iBoard_Col];


	int m_iXMove;
	int m_iYMove;
	int m_iP;

	int m_iPlayerNum;

	void sendMessage(string sMsg);
	void getMessage(vector<string>& inputMsg);

	void parseBoardState(string rawBoardState);

public:
	UKACMBotMsgHandler();
	~UKACMBotMsgHandler();
	
	void start();
		
	void setMyTurnMove(int iXPos, int iYPos, int iP);
	virtual void onMyTurn(int boardState[m_iBoard_Row][m_iBoard_Col], int iPlayerNum) = 0;

};

#endif