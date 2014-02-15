#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <map>
#include <set>
#include <time.h>

#include "Subprocess.h"
#include "piecegroup.h"
#include "board.h"
#include "common.h"

#define MAX_DATE 80
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

void logfile(int turn, string p1, string p2, Board board, string message) {
	time_t now;
   	char the_date[MAX_DATE];

   	the_date[0] = '\0';

   	now = time(NULL);

   	if (now != -1)
   	{
       strftime(the_date, MAX_DATE, "%H%M%S", localtime(&now));
   	}

   	//std::string(the_date);
	ofstream file;
	string name = "./goplayer/games/"+p1+"-"+p2+the_date+".game";
	file.open(name.c_str(), ios::out | ios::app);
	file << turn << "," << p1 << "," << p2 << "," << board.toString() << "," << message << endl;
	file.close();
}

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

	map<string, int> badMoves;
	badMoves[b1.name] = 0;
	badMoves[b2.name] = 0;
	
	map<string, int> captured;
	captured[b1.name] = 0;
	captured[b2.name] = 0;
	
	int turn = 0;
	string message = "";

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
			
			if(p == 1) {
				log(curBot->name,"Bot passes. Next bot turn.");
				message += curBot->name + " passes.";
				numPasses++;
				if(numPasses >= 2) {
					log(curBot->name,"Both bots passes. End game.");
					message += " Both bots have passed. Game over.";
					break;
				}
			} else {
				log(curBot->name,"Got move. Now resolving.");
				int* caps;
				if(turnBot1) {
					caps = board.place(x,y,WHITE);
					captured[b1.name] += caps[0];
					captured[b2.name] += caps[1];
				} else {
					caps = board.place(x,y,BLACK);
					captured[b1.name] += caps[1];
					captured[b2.name] += caps[0];
				}
				numPasses = 0;
				//cout << "[" << curBot->name << "]" << " Got move: " 
					//<< preX << " " << preY << " " << endl;
			}
			cout << b1.name << ": " << captured[b1.name] << " " << b2.name << ": " << captured[b2.name] << endl;
			cout << board.preview() << endl;
			
			preX = x;
			preY = y;
			preP = p;
			
		} catch(ReadTimeoutException ex) {
			cerr << "Bot has timed out! End game." << endl;
			message += "Bot has timed out. Game over.";
			break;
		} catch(IllegalMoveException ex) {
			cerr << "Illegal Move: " << ex.what() << endl;
			cerr << "This counts as a pass." << endl;
			badMoves[curBot -> name]++;
			numPasses++;

			message += curBot->name + " has made an error. Pass.";

			if (badMoves[curBot -> name] >= 3) {
				cerr << "Too many illegal moves. Game ending." << endl;
				message += " Too many illegal moves from " + curBot->name + ". Game over.";
				break;
			}

		} catch(BadMessageException ex) {
			cerr << "Bad Message: " << ex.what() << endl;
			break;
		} catch(exception ex) {
			cerr << "Unknown Exception: " << ex.what() << endl;
			break;
		}
		
		logfile(turn, b1.name, b2.name, board, message);
		
		message = "";
		turnBot1 = !turnBot1;
		turn++;
	}

	b1.process->writeline("ENDGAME");
	b2.process->writeline("ENDGAME");

	map<string,int> points;
	points[b1.name] = 0;
	points[b2.name] = 0;

	vector<Point> space;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board.at(i,j) == NONE) {
				space.push_back(Point(i,j));
			}
		}
	}
	vector<PieceGroup> territory = board.groupify(space);

	for (vector<PieceGroup>::iterator p = territory.begin(); p != territory.end(); ++p) {
		set<Point, PointCmp> edges = (*p).getEdges();
		bool allSame = true;

		Piece commonColor = board.at(*(edges.begin()));
		for (set<Point,PointCmp>::iterator e = edges.begin(); e != edges.end(); ++e) {
			Piece color = board.at(*e);
			if (color != commonColor) {
				allSame = false;
				break;
			}
		}

		if (allSame) {
			if (commonColor == WHITE) {
				points[b1.name] += (*p).pieces.size();
			}
			if (commonColor == BLACK) {
				points[b2.name] += (*p).pieces.size();
			}
		}
	}

	points[b1.name] -= captured[b2.name];
	points[b2.name] -= captured[b1.name];
	
	if (points[b1.name] < 0) points[b1.name] = 0;
	if (points[b2.name] < 0) points[b2.name] = 0;

	cout << b1.name << ": " << points[b1.name] << " " << b2.name << ": " << points[b2.name] << endl;
	
	message += " Final score: (" + to_string(points[b1.name]) + "-" + to_string(points[b2.name]) + ")";

	logfile(turn, b1.name, b2.name, board, message);

	return 0;
}
