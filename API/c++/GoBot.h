#ifndef GOBOT_H
#define GOBOT_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class GoBot{

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
	int convert(string a);
public:
	GoBot();
	~GoBot();
	
	void start();
		
	//void setMyTurnMove(int iXPos, int iYPos, int iP);
	virtual void onMyTurn(int boardState[m_iBoard_Row][m_iBoard_Col],int iPlayerNum, int &iNext_X_Move,int &iNext_Y_Move , int &iP) = 0;

};

#endif
