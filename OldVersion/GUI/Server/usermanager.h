#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>
#include <arpa/inet.h>
#include <vector>

#include "database.h"
#include "ranking.h"
#include "gamedeck.h"
#include "carddatabase.h"
#include "matchmaking.h"

using namespace std;

#define MAXDATASIZE 500
#define NUMBEROFDECK 5
#define DECKSIZE 20

class Server;
class ChatManager;
class Matchmaking;

class UserManager{
    struct sockaddr_in my_addr;
    int new_fd;
    int sockfd = 0;
    pthread_t currentThread = 0;
    ssize_t numbytes = 0;
    char msgClient[MAXDATASIZE];
    //-------------------------
    Database* myDatabase;
    CardDatabase* myCardDatabase;
    Ranking* myRanking;
    Server* myServer;
    Matchmaking* myMatchmaking;
    ChatManager* userChatManager;
    User* user;
    int gameSock = 0;
public:
    UserManager();
    UserManager(ClientSocket*, Database*, CardDatabase*, Ranking*, Matchmaking*, Server*);
    UserManager(const UserManager&);
    UserManager& operator=(const UserManager&);
    ~UserManager();

    void start();
    friend void* newConnection(void* arg);

    friend void* launchChat(void* args);
    void startChat();

    void receiveFromClient();
    void sendOKToClient();
    void sendNOToClient();
    void sendIDToClient(int);
    void sendRankingToClient();
    void sendStringToClient(string);
    void printNewConnection();
    void printEndConnection();
    void printBrutalDisconnect();
    void signIn();
    void signUp();
    void treatUser();
    void mainMenu();
    void collectionMenu();
    vector<int> convertMsgToDeck(string);
    vector<int> createRandomDeck();
    void searchAndLoadDecks(string);
    void initialiseNewUserDecks(string);
    int count(int,vector<int>);
    vector<int> basicCollectionVect();
    void updateDecksFile(string usrname, vector<int> deck, int index);
//~~~~~~ Database
    int getUserID(string);
    int verifPasswordInDatabase(int,char*);
    int hasUserInDatabase(string);
    void addUserInDatabase(string,string);
    void loadCollectionToClient(int);
//~~~~~~ Ranking
    void addUserInRanking(User*);
//~~~~~~ Duel
    void findOpponent(GameDeck);
    void DisconnectUser();
//-------- GUI
    void startGUI();

};

#endif // USERMANAGER_H
