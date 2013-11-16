#include "board.h"
#include <iostream>

using namespace std;

int main() {
	Board board;
	int white[3][2] = {{1,1},{0,1},{1,0},};
	int black[1][2] = {{0,0},};
	
	
	for(int i = 0; i < 3; i++) {
		board.place(white[i][0],white[i][1],WHITE);
		cout << board.preview() << endl;
	}
	
	for(int i = 0; i < 1; i++) {
		board.place(black[i][0],black[i][1],BLACK);
		cout << board.preview() << endl;
	}

	board.place(3,3,WHITE);
	cout << board.preview() << endl;
	
	return 0;
}
