#ifndef Player_HPP_
#define Player_HPP_

#include <vector>
#include <string>
#include <iostream>

//#include "GameDeck.hpp"
//#include "ChatManager.hpp"
#include "Card.hpp"
#include "User.hpp"
#include "GameDeck.hpp"

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
	void showPlayerCards();
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
	void receiveDamageOnMinion(int, int);
	int isDead();

	Player();
	Player(User*, GameDeck, int, ChatManager*);
	Player(const Player&);
	Player& operator=(const Player&);
	~Player();

	void startChat();
	int getChatFd();
	void printBrutalDisconnect();

};

#endif //Player_HPP_