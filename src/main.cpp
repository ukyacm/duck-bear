#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include "Subprocess.h"
#include "common.h"

using namespace std;

const int TIME_OUT = 4;

int main(int argc, char * argv[]) {
	string b1name(argv[1]);
	string b2name(argv[2]);
	
	cout << "New Game: " << b1name << " vs. " << b2name << endl << flush;
	
	//Board board;
	Subprocess bot1 = Subprocess::run(b1name);
	Subprocess bot2 = Subprocess::run(b2name);
	
	// make sure the processes are still alive
	assert(bot1.isAlive() && bot2.isAlive());
	
	try {
		// greet bot 1
		log(b1name,"Waiting for greeting..");
		string b1Greeting = bot1.readline(TIME_OUT);
		if(b1Greeting != "HI!")
			throw new BadMessageException(b1Greeting);
		
		log(b1name,"Received greeting.");
		
		bot1.writeline("INITIALIZE 1");
		
		string b1Ready = bot1.readline(TIME_OUT);
		if(b1Ready != "READY!")
			throw new BadMessageException(b1Ready);
		log(b1name,"Bot is ready!");
		
		// greet bot 2
		log(b2name,"Waiting for greeting..");
		string b2Greeting = bot2.readline(TIME_OUT);
		if(b2Greeting != "HI!")
			throw new BadMessageException(b2Greeting);
			
		log(b2name,"Received greeting.");
		bot2.writeline("INITIALIZE 1");
		
		string b2Ready = bot2.readline(TIME_OUT);
		if(b2Ready != "READY!")
			throw new BadMessageException(b2Ready);
		log(b2name,"Bot is ready!");
		
	} catch(ReadTimeoutException ex) {
		cerr << "[ReadTimeout] " << ex.what() << endl;
	} catch(BadMessageException ex) {
		cerr << "[BadMessage] " << ex.what() << endl;
	}
	
	/*
	bool turnBot1 = true;
	int preX = -1;
	int preY = -1;
	int preP = 1;
	while(true) {
		Subprocess * curBot;
		Piece piece;
		if(turnBot1) {
			curBot = &bot1;
			piece = WHITE;
		} else {
			curBot = &bot2;
			piece = BLACK;
		}
		
		try {
			// send move request
			string request = sprintf("REQUEST_MOVE %s %d %d %d", board.encoded(), preX, preY, preP);
			curBot->writeline(request);
			
			// handle move response
			string response = curBot->readline(TIME_OUT);
			stringstream ss(response);
			string msgType;
			int x, y, p;
			ss >> msgType >> x > y > p;
			
			
			if(msgType != "RESPONSE_MOVE")
				throw new BadMessageException(msgType);
				
			preX = x;
			preY = y;
			preP = p;
			
			board.place(x,y,piece);
			board.resolve();
		} catch(ReadTimeoutException ex) {
			cerr << "timed out" << endl;
			break;
		} catch(IllegalMoveException ex) {
			cerr << "illegal move: " << ex.what() << endl;
			break;
		} catch(BadMessageException ex) {
			cerr << "bad message: " << ex.what() << endl;
			break;
		} catch(exception ex) {
			cerr << "exception: " << ex.what() << endl;
			break;
		}
		
		turnBot1 = !turnBot1;
	}*/

	bot1.writeline("ENDGAME");
	bot2.writeline("ENDGAME");
	
	return 0;
}
