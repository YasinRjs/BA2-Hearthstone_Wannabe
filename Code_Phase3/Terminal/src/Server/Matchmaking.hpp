#ifndef Matchmaking_HPP_
#define Matchmaking_HPP_

#define MAXDATASIZE 500

#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include "ChatManager.hpp"
#include "User.hpp"
#include "Player.hpp"
#include "GameDeck.hpp"
#include "Game.hpp"
#include "Server.hpp"

using namespace std;

class ChatManager;
class Server;
class Game;

class Matchmaking{
	vector<User*> userInMatchmaking;
	vector<int> userGameSockets;
	vector<GameDeck> userDecks;
	vector<ChatManager*> userChatManagers;
	vector<Game*> gameInProgress;
	int numberGames;
	Server* myServer;
public:
	Matchmaking();
	Matchmaking(Server*);
	Matchmaking(const Matchmaking&);
	Matchmaking& operator=(const Matchmaking&);
	~Matchmaking();

	void addUserInMatchmaking(User*, int, GameDeck, ChatManager*);
	void createGame(User*, int, GameDeck, ChatManager*, User*, int, GameDeck, ChatManager* cm2);
};


#endif // Matchmaking_HPP_