#ifndef MATCHMAKING_H
#define MATCHMAKING_H

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

#include "chatmanager.h"
#include "user.h"
#include "player.h"
#include "gamedeck.h"
#include "game.h"
#include "server.h"

using namespace std;

class ChatManager;
class Server;
class Game;

class Matchmaking{
    vector<User*> userInMatchmaking;
    vector<int> userGameSockets;
    vector<GameDeck> userDecks;
    vector<ChatManager*> userChatManagers;
    vector<int> userGameFd;
    vector<Game*> gameInProgress;
    int numberGames;
    Server* myServer;
public:
    Matchmaking();
    Matchmaking(Server*);
    Matchmaking(const Matchmaking&);
    Matchmaking& operator=(const Matchmaking&);
    ~Matchmaking();

    void addUserInMatchmaking(User*, int, GameDeck, ChatManager*, int);
    void createGame(User*, int, GameDeck, ChatManager*, User*, int, GameDeck, ChatManager* cm2, int, int);
};

#endif // MATCHMAKING_H
