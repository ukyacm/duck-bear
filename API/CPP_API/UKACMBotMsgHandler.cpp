#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <cstddef>

#include "UKACMBotMsgHandler.h"

using namespace std;

UKACMBotMsgHandler::UKACMBotMsgHandler(void){
	
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


UKACMBotMsgHandler::~UKACMBotMsgHandler(){

}

void UKACMBotMsgHandler::sendMessage(string sMsg){
	cout << sMsg << "\n";
	cout << flush;
}

void UKACMBotMsgHandler::getMessage(vector<string>& inputMsg){
	inputMsg.clear();
	char str[256];
	memset((void*) str, 0, 256*sizeof(char));
	cin.getline(str,256,'\n');
	//str = "INITIALIZE 1";
	istringstream ss(str);

	for(string word; ss >> word; inputMsg.push_back(word));
}

void UKACMBotMsgHandler::start(){
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



	while(1){
		getMessage(inputMsg);

		if ( inputMsg[0]== "INITIALIZE"){
		m_iPlayerNum = atoi(inputMsg[1].c_str());
		sendMessage("READY!");
		}
		else if (inputMsg[0] == "REQUEST_MOVE"){			
			parseBoardState(inputMsg[1]);
			onMyTurn(m_Board,m_iPlayerNum);
			stringstream sout;
			sout << "RESPONSE_MOVE " << m_iXMove << " " << m_iYMove << " " << m_iP;
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

void UKACMBotMsgHandler::setMyTurnMove(int iXPos, int iYPos, int iP){
	m_iXMove = iXPos;
	m_iYMove = iYPos;
	m_iP = iP;

}

void UKACMBotMsgHandler::parseBoardState(string rawBoardState){
	int iTotalBoardSize = m_iBoard_Row*m_iBoard_Col;

	if (rawBoardState.size() != iTotalBoardSize){
		//cout << "incomplete board state array data\n";
		exit(EXIT_FAILURE);
	}

	
	for ( int currPos = 0 ; currPos < iTotalBoardSize; ++currPos){
		int iRow = currPos/m_iBoard_Row;
		int iCol = currPos%m_iBoard_Col;
		m_Board[iRow][iCol] = rawBoardState[currPos];
		++currPos;
	}
}
