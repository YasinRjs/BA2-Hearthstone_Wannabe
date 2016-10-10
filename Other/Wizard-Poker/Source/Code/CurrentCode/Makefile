CLT_OBJS = Client/mainClient.cpp Client/Deck.cpp Client/Collection.cpp Client/Client.cpp
SRV_OBJS = Server/mainServer.cpp Server/Server.cpp Server/Card.cpp Server/CardDatabase.cpp Server/ChatManager.cpp Server/ClientSocket.cpp Server/Database.cpp Server/User.cpp Server/UserManager.cpp Server/Ranking.cpp Server/Matchmaking.cpp Server/GameDeck.cpp Server/Player.cpp Server/Game.cpp
TARGET=clean echoClean client server
CC=g++-5
CFLAGS = -std=c++14 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -Wzero-as-null-pointer-constant
LIBS = -lpthread
PRINT="--- Les binaires ont été éffacés ---"

normal: $(TARGET)

client: Client/mainClient.cpp
	$(CC) $(CLT_OBJS) $(LIBS) $(CFLAGS) -o client

server: Server/mainServer.cpp
	$(CC) $(SRV_OBJS) $(LIBS) $(CFLAGS) -o server

mainClient: Client/mainClient.cpp
	$(CC) $(CFLAGS) Client/mainClient.cpp -c

mainServer: Server/mainServer.cpp
	$(CC) $(CFLAGS) Server/mainServer.cpp -c

ClientSocket: Server/ClientSocket.cpp Server/ClientSocket.hpp
	$(CC) $(CFLAGS) Server/ClientSocket.cpp -c

ChatManager: Server/ChatManager.cpp Server/ChatManager.hpp
	$(CC) $(CFLAGS) Server/ChatManager.cpp -c

Collection: Client/Collection.cpp Client/Collection.hpp
	$(CC) $(CFLAGS) Client/Collection.cpp -c

Database: Server/Database.cpp Server/Database.hpp
	$(CC) $(CFLAGS) Server/Database.cpp -c

Deck: Client/Deck.cpp Client/Deck.hpp
	$(CC) $(CFLAGS) Client/Deck.cpp -c

Game: Server/Game.cpp Server/Game.hpp
	$(CC) $(CFLAGS) Server/Game.cpp -c

Ranking: Server/Ranking.cpp Server/Ranking.hpp
	$(CC) $(CFLAGS) Server/Ranking.cpp -c

User: Server/User.cpp Server/User.hpp
	$(CC) $(CFLAGS) Server/User.cpp -c

UserManager: Server/UserManager.cpp Server/UserManager.hpp
	$(CC) $(CFLAGS) Server/UserManager.cpp -c

Matchmaking: Server/Matchmaking.cpp Server/Matchmaking.hpp
	$(CC) $(CFLAGS) Server/Matchmaking.cpp -c

Player: Server/Player.cpp Server/Player.hpp
	$(CC) $(CFLAGS) Server/Player.cpp -c

Client: Client/Client.cpp Client/Client.hpp
	$(CC) $(CFLAGS) Client/Client.cpp -c

Server: Server/Server.cpp Server/Server.hpp
	$(CC) $(CFLAGS) Server/Server.cpp -c

echoClean:
	@echo $(PRINT)

clean:
	$(RM) $(TARGET)