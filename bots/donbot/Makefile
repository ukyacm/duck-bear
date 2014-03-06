SRC_DIR = src

donbot: DonBot.o GoBot.o board.o common.o piecegroup.o
	g++ DonBot.o GoBot.o $(SRC_DIR)/board.o $(SRC_DIR)/common.o $(SRC_DIR)/piecegroup.o -g -Wall -o donbot

DonBot.o: ./DonBot.cpp ./DonBot.h
	g++ -c -g -Wall ./DonBot.cpp -o DonBot.o

GoBot.o: ./GoBot.cpp ./GoBot.h
	g++ -c -g -Wall ./GoBot.cpp -o GoBot.o
	
common.o: $(SRC_DIR)/common.cpp $(SRC_DIR)/common.h
	g++ -c $(SRC_DIR)/common.cpp -o $(SRC_DIR)/common.o
	
board.o: $(SRC_DIR)/board.cpp $(SRC_DIR)/board.h
	g++ -c $(SRC_DIR)/board.cpp -o $(SRC_DIR)/board.o
	
piecegroup.o: $(SRC_DIR)/piecegroup.cpp $(SRC_DIR)/piecegroup.h
	g++ -c $(SRC_DIR)/piecegroup.cpp -o $(SRC_DIR)/piecegroup.o

clean:
	rm -rf *.o donbot
