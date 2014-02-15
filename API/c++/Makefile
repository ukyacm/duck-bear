ExampleBot: ExampleBot.o GoBot.o
	g++ ExampleBot.o GoBot.o -g -Wall -o examplebot

ExampleBot.o: ./ExampleBot.cpp ./ExampleBot.h
	g++ -c -g -Wall ./ExampleBot.cpp -o ExampleBot.o

GoBot.o: ./GoBot.cpp ./GoBot.h
	g++ -c -g -Wall ./GoBot.cpp -o GoBot.o

clean:
	rm -rf *.o examplebot
