#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fstream>
#include <sstream>

// -------------New------------------ //
#include "deck.h"
#include "collection.h"
#define NUMBEROFDECK 5
#define DECKSIZE 20
// -------------New------------------ //

#define MAXDATASIZE 500
#define PORT 5555

using namespace std;

class Client{
    char inputPlayer[MAXDATASIZE] = "nothing";
    char msgServer[MAXDATASIZE] = "nothing";
    int sockfd = 0;
    ssize_t numbytes = 0;
    struct sockaddr_in my_addr;
    struct hostent *he;
    int rcvChat_fd = 0;
    int sendChat_fd = 0;
    ssize_t rcvNumbytes = 0;
    ssize_t sendNumbytes = 0;
    int gameOver = 0;
    pthread_t chatThread = 0;
    char msgRcvChat[MAXDATASIZE] = "nothing";
    char msgSendChat[MAXDATASIZE] = "nothing";
    string clientUsername = "None";
    // -------------New------------------ //
    Collection myCollection;
    Deck myDecks[5];
    Deck myBufferDecks [5];
    string activeDeck = "nothing";
    // -------------New------------------ //
    string username = "none";
    string password = "none";
    int launchDuel = 0;
    int gameSocket = 0;
    char waitMsg[MAXDATASIZE] = "nothing";
    int handSize = 0;
    int canAtk = 0;
    int targetSize = 0;

public:
    Client();
    Client(int argSize,char* ip);
    ~Client();
    Client(const Client&);
    Client& operator= (const Client&);

    void verifArgs(int argSize);
    void init(char* ip);
    void welcomeMsg();
    void traceLigne();
    void traceDiese();
    void leaveMsg();
    void askConnection();
    void sendInputToServer();
    void receiveFromServer();
    void signIn();
    void signUp();
    void showOneDeck();
    void showOneCard();
    void removeOneDeck();
    void loadCollection();
    void printRanking();
    void mainMenu();
    int isCorrectInput(char*);
    void collectionMenu();
    void printDecks();
    void printCollection();
    int choseDeck();
    void createNewDeckNumber(int);
    void addIDinDeck(int,int);
    int hasIDinCollection(int);
    void removeDeckatIndex(int);
    string convertDeckToString(int);
//----------------------------------------
    void sendStringToServer(string);
    void sendConfirmation(int);
    void startReception();
    friend void* receiveChat(void* arg);
    void receiveMsgFromPlayer();
    void chatReception();
    void sendMsgToChatManager(char*);
    void receiveFromChatManager();
    void startChat();
    void giveMsg();
//-------------------------------------
    void findOpponent();
    void startGame();
    void printGameStarting();

    void actionMenu();
    int isMyTurn();
    int isWaitingTurn();
    int askPlayCard();
    int askAttack();
    int askChat();
    int finishTurn();
    void choseMenu();
    void choseCard();
    void choseMinionAndTarget();
    void choseTarget();
    void choseMinion();
    void surrender();
    void endTurn();
    void waitingTurn();
    void printWinning();
    void printLosing();
    void infoSurrender();
    void infoKill();
    void infoEndGame();
//----------------------------------------
    void setDeck(Deck,int);
    void loadDecks();
    int count(int,vector<int>);
    void initialiseAllDecks();
    void modifyDeck(string);
    size_t positionOfAnElement(int,vector<int>);
    bool find(int,vector<int>);
    void printDeck(vector<int>);
    void updateDecksFile(string);
    void removeDeck(string);
    int isCorrectInputForCollecMenu(char*);
    int numberOfDecksFilled();
    int emptyDeckAtPosition();
    void createNewDeck(string);
    void fillTheDeckAtPosition(int);

    string getMsgServer();
    char* getMsgSendChat();
    char* getMsgRecvChat();
    void resetMsgSendChat();
    int getSockfd();
    int getSendChatfd();
    int getRecvChatfd();
    void setUsername(string);
    string getUsername();
    void setPassword(string);
    string parseOneDeck(int);
    void setActiveDeck(string);
    string getActiveDeck();
    Collection getCollection();
    Deck getDeck(int);
    Deck getBufferDeck(int);
    void setBufferDeck(Deck newDeck,int indice);

    void setLaunchDuel(int);
    int getLaunchDuel();
    void connectInGame();
    void receiveFromGameSocket();
    string getWaitMsg();
    void setHandSize(int);
    int getHandSize();
    void setCanAtk(int);
    int getCanAtk();
    void setTargetSize(int);
    int getTargetSize();
    bool canPutInDeck(vector<int> deck, int id);
    void createNewDeckFromVector(vector<int> listId, string username);
    void setMsg(string);
};

#endif // CLIENT_H
