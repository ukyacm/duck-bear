#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cstddef>

#include "GoBot.h"

using namespace std;

GoBot::GoBot(void){
	
	m_iXMove = -1;
	m_iYMove = -1;
	m_iP= -1;

	m_iPlayerNum = -1;

	for (int iRow = 0 ; iRow < m_iBoard_Row ; ++iRow){
		for (int iCol =0; iCol < m_iBoard_Col; ++iCol){
			m_Board[iRow][iCol] = 0;
		}
	}

}


GoBot::~GoBot(){

}

void GoBot::sendMessage(string sMsg){
	//cerr << "message sent is "<< sMsg << "\n";
	cout << sMsg << "\n";
	cout << flush;
}

void GoBot::getMessage(vector<string>& inputMsg){
	m_iXMove = -1;
	m_iYMove = -1;
	m_iP= -1;
	//cerr << m_iXMove << " " << m_iYMove << "  This is getting msg" << endl;
	inputMsg.clear();
	char str[256];
	memset((void*) str, 0, 256*sizeof(char));
	cin.getline(str,256,'\n');

	//str = "INITIALIZE 1";
	istringstream ss(str);
	//cerr << str << " is the message got" << endl;
	for(string word; ss >> word; inputMsg.push_back(word));
}

void GoBot::start(){
	sendMessage("HI!");
	
	vector<string> inputMsg;
	//getMessage(inputMsg);

	/*if ( inputMsg[0]== "INITIALIZE"){
		m_iPlayerNum = atoi(inputMsg[1].c_str());
		sendMessage("READY!");
	}
	*/
	/*
	else
	{
		//cout << "bad message, expect init\n";
		exit(EXIT_FAILURE);
	}
	*/

	getMessage(inputMsg);

	if ( inputMsg[0]== "INITIALIZE"){
		m_iPlayerNum = atoi(inputMsg[1].c_str());
		sendMessage("READY!");
	}
	else{
		exit(EXIT_FAILURE);
	}


	string lastMsg = "";
	while(1){
		
		getMessage(inputMsg);

		if (inputMsg[0] == "REQUEST_MOVE"){
			//cerr << "omG" << endl;			
			//cerr << "REQUEST_MOVE_DEBUG" << inputMsg[1] << endl; 
			parseBoardState(inputMsg[1]);
			int x_move = -1 , y_move = -1, iPass = -1;
			onMyTurn(m_Board,m_iPlayerNum,x_move,y_move,iPass);
			stringstream sout;
			sout << "RESPONSE_MOVE " << x_move << " " << y_move << " " << iPass;
			string moveMsg = sout.str();
			sendMessage(moveMsg);
		}
		else if( inputMsg[0] == "END_GAME"){
			exit(EXIT_FAILURE);
		}
		else{
			//cout << "bad msg, expected move; got '"  << inputMsg[0] << "'\n";
			exit(EXIT_FAILURE);
		}
	
	}

}

/*
void GoBot::setMyTurnMove(int iXPos, int iYPos, int iP){
	//cerr << iXPos << " " << iYPos << " " << endl;
	m_iXMove = iXPos;
	m_iYMove = iYPos;
	m_iP = iP;

}*/

void GoBot::parseBoardState(string rawBoardState){
	unsigned int iTotalBoardSize = 9*9;

	if (rawBoardState.size() != iTotalBoardSize){
		//cout << "incomplete board state array data\n";
		exit(EXIT_FAILURE);
	}

	//cerr << " rawBoardState" << rawBoardState << endl;
	//cerr << "new Board " << endl;
	for (unsigned int currPos = 0 ; currPos < iTotalBoardSize; currPos++){
		unsigned int iRow = currPos/9;
		unsigned int iCol = currPos%9;
		////cerr << rawBoardState[currPos];
		int iNumConverted = convert(rawBoardState.substr(currPos,1));
		////cerr << "Coverted value to " << iNumConverted << endl;
		m_Board[iRow][iCol] = iNumConverted;
	}
}

int GoBot::convert(string a){
	////cerr << "print out value " << a;
	if ( a == "1")
		return 1;
	if ( a == "2")
		return 2;
	if ( a == "0")
		return 0;

	return -1;
}
