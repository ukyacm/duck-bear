#include <cassert>
#include <iostream>
#include <vector>
#include "Subprocess.h"
#include "board.h"

using namespace std;

int main(int argc, char * argv[]) {
	Subprocess bot1 = Subprocess::run(argv[1]);
	Subprocess bot2 = Subprocess::run(argv[2]);
	
	assert(bot1.isAlive() && bot2.isAlive());
	
	for(int i = 0; i < 8; i++) {
		if(!proc.isAlive())
			break;
		proc.writeline("m");
		string response;
		try {
			response = proc.readline(9);
		} catch(ReadTimeoutException ex) {
			cout << "timed out" << endl;
			continue;
		}
		
		cout << response << endl;
	}
	
	response = bot1.readline(9);
	
	
	bot1.die();
	bot2.die();
	
	return 0;
}
