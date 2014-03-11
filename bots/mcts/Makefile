MCTSBot: MCTSBot.o Node.o GoBot.o common.o board.o piecegroup.o
	g++ -O2 MCTSBot.o Node.o GoBot.o common.o board.o piecegroup.o -g -Wall -o MCTSBot

MCTSBot.o: MCTSBot.cpp MCTSBot.h
	g++ -c -g -O2 -Wall MCTSBot.cpp -o MCTSBot.o

Node.o: Node.cpp Node.h
	g++ -c -g -O2 -Wall Node.cpp -o Node.o

GoBot.o: GoBot.cpp GoBot.h
	g++ -c -g -O2 -Wall GoBot.cpp -o GoBot.o

common.o: common.cpp common.h
	g++ -c -O2 common.cpp -o common.o

board.o: board.cpp board.h
	g++ -c -O2 board.cpp -o board.o

piecegroup.o: piecegroup.cpp piecegroup.h
	g++ -c -O2 piecegroup.cpp -o piecegroup.o

clean:
	rm -rf *.o MCTSBot
