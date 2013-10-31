TestBot: testBot.o UKACMGoAPI.o UKACMBotMsgHandler.o
		g++ testBot.o UKACMGoAPI.o UKACMBotMsgHandler.o -g -Wall -o TestBot
		
testBot.o: ./testBot.cpp
		g++ -c  -g -Wall ./testBot.cpp -o ./testBot.o

UKACMGoAPI.o: ./UKACMGoAPI.cpp ./UKACMGoAPI.h
		g++ -c -g -Wall ./UKACMGoAPI.cpp -o UKACMGoAPI.o

UKACMBotMsgHandler.o: ./UKACMBotMsgHandler.cpp ./UKACMBotMsgHandler.h
		g++ -c -g -Wall ./UKACMBotMsgHandler.cpp -o UKACMBotMsgHandler.o

clean:
		rm -rf *.o TestBot