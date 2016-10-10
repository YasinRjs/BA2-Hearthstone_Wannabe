#ifndef GAME_H
#define GAME_H

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

#define MAXSEND 500

#include "player.h"
#include "server.h"

using namespace std;

class Player;
class Server;

class Game{
    Server* myServer;
    Player* player1;
    Player* player2;
    int inProgress;
    ssize_t numbytes;
    ssize_t num;
    char msgPlayer[MAXSEND] = "nothing";
    Player* currentPlayer;
    Player* waitingPlayer;
    int endTurn;
    int gameOver;
    int totalTurn;
public:
    Game();
    Game(Server*,Player*,Player*);
    Game(const Game&);
    Game& operator=(const Game&);
    ~Game();

    void initGame();
    void startGame();
    void startTurn();

    void yourTurn();
    void waitOpponentTurn();

    void sendStringToPlayer(Player*, string);
    void receiveFromPlayer(Player*);
    string convertHandToString(Player*);
    string convertBoardToString(Player*, Player*);

    string ableToAttackInBoard();
    void restoreAtkToMinions();

    void sendBoards();
    void sendBoardToWaiting();
    void sendBoardAndHand(Player*, Player*);

    void sendStartTurnToPlayers();
    void turnNotFinished();
    void summon(Card);
    int canPlayCard(Card);
    void removeCardFromPlayerHand(int);

    int isRunning();
    string giveTargets(Player*);

    void playerDisconnected();

    int isNotEmptyMsg();
    void trySummon();
    void tryUsingCard();
    void askOneCard();
    void playOneCard();

    int askPlayCard();
    int askAttack();
    int askChat();
    int askFinishTurn();
    int askSurrender();

    void tryAttack();
    void doAttack(int);
    void updateCanAtk(int);
    void activeCheatEnergy();

    void sendTargets();
    void findTarget(int);
    void finishTurn();
    void surrender();
    void attackPlayer(int);
    void checkPlayerIsDead();

    void infoEndGame();
    void sendInfoKill(int);
    string guiConvertBoard(Player*, Player*);
    string guiConvertHand(Player*);
    void guiSendBoardToWaiting();
    void guiSendBoardAndHand(Player*,Player*);
    void connectPlayer();
    void surrenderGui();
    int askDisconnected();
    void disconnected();
};

#endif // GAME_H
