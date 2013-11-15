#include "board.h"
#include <iostream>

using namespace std;

int main() {
	Board board;
	int white[4][2] = {{2,1}, {5,1}, {5,2},{4,2}};
	int black[7][2] = {{6,1},{4,1},{3,2},{4,3},{5,0},{5,3},{6,2}};
	
	
	for(int i = 0; i < 4; i++) {
		board.place(white[i][0],white[i][1],WHITE);
		cout << board.preview() << endl;
	}
	
	for(int i = 0; i < 7; i++) {
		board.place(black[i][0],black[i][1],BLACK);
		cout << board.preview() << endl;
	}
	
	return 0;
}
