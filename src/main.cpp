#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include "Subprocess.h"
#include "board.h"
#include "common.h"

using namespace std;

const int TIME_OUT = 4;

struct Bot {
	Subprocess * process;
	string command;
	string name;
	void ExtractBotName(){
		int lastIndex = -1;
		int lastDotIndex = -1;
		int length = command.length();
		for (int i = 0; i < length ; ++i) {
			if ((command[i] >= 65 && command[i] <= 90) 
			|| (command[i] >= 97 && command[i] <= 122)
			|| (command[i] >= 48 && command[i]<= 57 )
			){
				continue;
			}
			if (command[i] == 46){
				lastDotIndex = i;
			}
			else
			{
				lastIndex = i;
			}
		}

		if (lastIndex > 0 || lastDotIndex > 0){
			if (lastDotIndex>lastIndex && lastIndex < 0){
				name = command.substr(0,lastDotIndex);
			}
			if (lastDotIndex>lastIndex && lastIndex > 0){
				int includeLen = lastDotIndex-1 - lastIndex;
				name = command.substr(lastIndex+1,includeLen);
			}
			if (lastDotIndex < lastIndex && lastIndex > 0){
				int includeLen = length- lastIndex;
				name = command.substr(lastIndex+1,includeLen);
			}
		}
		else
		{
			name = command;
		}
	}
};

int main(int argc, char * argv[]) {	
	Bot b1;
	Bot b2;
	b1.command = argv[1];
	b2.command = argv[2];
	
	// figure out the names
	//int lastindex1 = b1.command.find_last_of(".");
	//int lastindex2 = b2.command.find_last_of(".");
	//b1.name = b1.command.substr(0, lastindex1); 
	//b2.name = b2.command.substr(0, lastindex2); 
	b1.ExtractBotName();
	b2.ExtractBotName();
	if(b1.name == b2.name) {
		b1.name += "1";
		b2.name += "2";
	}
	
	cout << "New Game: " << b1.name << " vs. " << b2.name << endl << flush;
	
	//Board board;
	Subprocess sp1 = Subprocess::run(b1.command);
	Subprocess sp2 = Subprocess::run(b2.command);
	b1.process = &sp1;
	b2.process = &sp2;
	
	// make sure the processes are still alive
	assert(b1.process->isAlive() && b2.process->isAlive());
	
	Board board;
	
	try {
		// greet bot 1
		log(b1.name,"Waiting for greeting..");
		string b1Greeting = b1.process->readline(TIME_OUT);
		if(b1Greeting != "HI!")
			throw new BadMessageException(b1Greeting);
		
		log(b1.name,"Received greeting.");
		
		b1.process->writeline("INITIALIZE 1");
		
		string b1Ready = b1.process->readline(TIME_OUT);
		if(b1Ready != "READY!")
			throw new BadMessageException(b1Ready);
		log(b1.name,"Bot is ready!");
		
		// greet bot 2
		log(b2.name,"Waiting for greeting..");
		string b2Greeting = b2.process->readline(TIME_OUT);
		if(b2Greeting != "HI!")
			throw new BadMessageException(b2Greeting);
			
		log(b2.name,"Received greeting.");
		b2.process->writeline("INITIALIZE 1");
		
		string b2Ready = b2.process->readline(TIME_OUT);
		if(b2Ready != "READY!")
			throw new BadMessageException(b2Ready);
		log(b2.name,"Bot is ready!");
		
	} catch(ReadTimeoutException ex) {
		cerr << "[GreetingReadTimeout] " << ex.what() << endl;
	} catch(BadMessageException ex) {
		cerr << "[GreetingBadMessage] " << ex.what() << endl;
	}
	
	// track game state
	bool turnBot1 = true;
	int preX = -1;
	int preY = -1;
	int preP = 1;
	int numPasses = 0;
	
	while(true) {
		Bot * curBot = 0;
		
		// figure out the bot to interact with
		if(turnBot1) {
			curBot = &b1;
		} else {
			curBot = &b2;
		}
		
		try {
			// send move request
			stringstream request;
			request << "REQUEST_MOVE " << board.toString();
			request << " " << preX << " " << preY << " " << preP;
			curBot->process->writeline(request.str());
			//cout << request.str() << endl;
			log(curBot->name,"Sent request for move..");
			
			// handle move response
			string response = curBot->process->readline(TIME_OUT);
			stringstream ss(response);
			string msgType;
			int x, y, p;
			ss >> msgType >> x >> y >> p;
			
			if(msgType != "RESPONSE_MOVE")
				throw BadMessageException(msgType);
			
			if(preP == 1) {
				log(curBot->name,"Bot passes. Next bot turn.");
				numPasses++;
				if(numPasses >= 2) {
					log(curBot->name,"Both bots passes. End game.");
					break;
				}
			} else {
				log(curBot->name,"Got move. Now resolving.");
				if(turnBot1)
					board.place(x,y,WHITE);
				else
					board.place(x,y,BLACK);
				
				numPasses = 0;
				//cout << "[" << curBot->name << "]" << " Got move: " 
					//<< preX << " " << preY << " " << endl;
			}
			cout << board.preview() << endl;
			
			preX = x;
			preY = y;
			preP = p;
			
		} catch(ReadTimeoutException ex) {
			cerr << "Bot has timed out! End game." << endl;
			break;
		} catch(IllegalMoveException ex) {
			cerr << "Illegal Move: " << ex.what() << endl;
			cerr << "Moving on.." << endl;
			numPasses++;
		} catch(BadMessageException ex) {
			cerr << "Bad Message: " << ex.what() << endl;
			break;
		} catch(exception ex) {
			cerr << "Unknown Exception: " << ex.what() << endl;
			break;
		}
		
		turnBot1 = !turnBot1;
	}

	b1.process->writeline("ENDGAME");
	b2.process->writeline("ENDGAME");
	
	return 0;
}
