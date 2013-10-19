SRC_DIR = src

GoEngine: common.o Subprocess.o main.o board.o
	g++ $(SRC_DIR)/main.o $(SRC_DIR)/common.o $(SRC_DIR)/Subprocess.o -lrt -o GoEngine

common.o: $(SRC_DIR)/common.cpp $(SRC_DIR)/common.h
	g++ -c $(SRC_DIR)/common.cpp -o $(SRC_DIR)/common.o

Subprocess.o: $(SRC_DIR)/Subprocess.cpp $(SRC_DIR)/Subprocess.h
	g++ -c $(SRC_DIR)/Subprocess.cpp -o $(SRC_DIR)/Subprocess.o

main.o: $(SRC_DIR)/main.cpp
	g++ -c $(SRC_DIR)/main.cpp -o $(SRC_DIR)/main.o

board.o: $(SRC_DIR)/board.cpp $(SRC_DIR)/board.h
	g++ -c $(SRC_DIR)/board.cpp -o $(SRC_DIR)/board.o

clean:
	rm -rf src/*.o GoEngine
