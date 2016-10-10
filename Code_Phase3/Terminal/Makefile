CLT_OBJS = src/Client/mainClient.cpp src/Client/Deck.cpp src/Client/Collection.cpp src/Client/Client.cpp
SRV_OBJS = src/Server/mainServer.cpp src/Server/Server.cpp src/Server/Card.cpp src/Server/CardDatabase.cpp src/Server/ChatManager.cpp src/Server/ClientSocket.cpp src/Server/Database.cpp src/Server/User.cpp src/Server/UserManager.cpp src/Server/Ranking.cpp src/Server/Matchmaking.cpp src/Server/GameDeck.cpp src/Server/Player.cpp src/Server/Game.cpp
TARGET=clean echoClean client server
CTARGET=client server
CC=@g++-5
RM=@rm -f
CFLAGS = -std=c++14 -Wpedantic -Wall -Wextra -Winit-self -Winline -Wconversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wconversion -Wsign-promo -Wzero-as-null-pointer-constant
LIBS = -lpthread
TDONE="--- Task completed ---"
DONE="--- All targets have been built and compiled ---"

normal: $(TARGET)

client: src/Client/mainClient.cpp
	@echo "Compiling client objects..."
	$(CC) $(CLT_OBJS) $(LIBS) $(CFLAGS) -o client
	@echo $(TDONE)

server: src/Server/mainServer.cpp
	@echo "Compiling server objects..."
	$(CC) $(SRV_OBJS) $(LIBS) $(CFLAGS) -o server
	@echo $(TDONE)
	@echo $(DONE)

mainClient: src/Client/mainClient.cpp
	@echo "test"
	$(CC) $(CFLAGS) src/Client/mainClient.cpp -c

mainServer: src/Server/mainServer.cpp
	$(CC) $(CFLAGS) src/Server/mainServer.cpp -c

ClientSocket: src/Server/ClientSocket.cpp src/Server/ClientSocket.hpp
	$(CC) $(CFLAGS) src/Server/ClientSocket.cpp -c

ChatManager: src/Server/ChatManager.cpp src/Server/ChatManager.hpp
	$(CC) $(CFLAGS) src/Server/ChatManager.cpp -c

Collection: src/Client/Collection.cpp src/Client/Collection.hpp
	$(CC) $(CFLAGS) src/Client/Collection.cpp -c

Database: src/Server/Database.cpp src/Server/Database.hpp
	$(CC) $(CFLAGS) src/Server/Database.cpp -c

Deck: src/Client/Deck.cpp src/Client/Deck.hpp
	$(CC) $(CFLAGS) src/Client/Deck.cpp -c

Game: src/Server/Game.cpp src/Server/Game.hpp
	$(CC) $(CFLAGS) src/Server/Game.cpp -c

Ranking: src/Server/Ranking.cpp src/Server/Ranking.hpp
	$(CC) $(CFLAGS) src/Server/Ranking.cpp -c

User: src/Server/User.cpp src/Server/User.hpp
	$(CC) $(CFLAGS) src/Server/User.cpp -c

UserManager: src/Server/UserManager.cpp src/Server/UserManager.hpp
	$(CC) $(CFLAGS) src/Server/UserManager.cpp -c

Matchmaking: src/Server/Matchmaking.cpp src/Server/Matchmaking.hpp
	$(CC) $(CFLAGS) src/Server/Matchmaking.cpp -c

Player: src/Server/Player.cpp src/Server/Player.hpp
	$(CC) $(CFLAGS) src/Server/Player.cpp -c

Client: src/Client/Client.cpp src/Client/Client.hpp
	$(CC) $(CFLAGS) src/Client/Client.cpp -c

Server: src/Server/Server.cpp src/Server/Server.hpp
	$(CC) $(CFLAGS) src/Server/Server.cpp -c

echoClean:
	@echo $(TDONE)

clean:
	@echo "Cleaning build targets..."
	$(RM) $(CTARGET)