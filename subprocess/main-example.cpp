#include <cassert>
#include <iostream>
#include <vector>
#include "Subprocess.h"

using namespace std;

int main(int argc, char * argv[]) {
	Subprocess proc = Subprocess::run("subprocess-example.py");
	
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
	
	proc.die();
	
	return 0;
}
