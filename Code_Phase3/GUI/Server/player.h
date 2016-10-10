#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <iostream>

#include "card.h"
#include "user.h"
#include "gamedeck.h"
#include "chatmanager.h"

using namespace std;

class ChatManager;

class Player{

    User* myUser;
    GameDeck myDeck;
    vector<Card> myHand;
    ChatManager* userChatManager; // PAS DE DELETE CHER YASIN!!!!
    vector<Card> myBoard;
    vector<int> canAtk;

    int hp;
    int energy;
    int currentEnergy;

    int sockt;
    int myTurn;

    int waitingSocket = 0;

public:
    void drawCard();
    void startNewTurn();
    void gainEnergy();
    void useCard(Card);
    void putInGraveyard(Card);
    void summon(Card);

    void addEnergy();
    void useEnergy(int);
    void restoreEnergy();
    void drawFirstCards();
    void win();
    void lose();
    void receiveDamage(int);
    //void showPlayerCards();
    int isMyTurn();
    void setTurn();
    void endTurn();
    void turnMenu();
    vector<Card>* getBoard();
    Card getCardInBoard(size_t);
    void addCanAtkMinion(size_t);
    void allMinionsCanAtk();

    int getSocket();
    vector<Card>* getHand();
    void clearBoardAtk();
    size_t getCanAtkSize();
    void eraseCanAtk(int);
    void updateCanAtkIndice(int);

    string getUsername();
    int getHP();
    int getCurrentEnergy();
    size_t getHandSize();
    void addBoard(Card);
    size_t getBoardSize();
    int nbrCanAttack();
    int getCanAtk(int);
    int getCanAtkIndice(int);
    void disableAtkCardInBoard(int);
    int receiveDamageOnMinion(int, int);
    int isDead();

    Player();
    Player(User*, GameDeck, int, ChatManager*, int game_fd);
    Player(const Player&);
    Player& operator=(const Player&);
    ~Player();

    void startChat();
    int getChatFd();
    void printBrutalDisconnect();
    void setWaitingSocket(int);
    void sendStringToWaitSocket(string);

};

#endif // PLAYER_H
