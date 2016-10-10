#include "GameDeck.hpp"

GameDeck::GameDeck() : myDeck(vector<Card>()),cardsLeftInDeck(0){}

GameDeck::GameDeck(vector<Card> vctCard) : myDeck(vctCard),cardsLeftInDeck(static_cast<int>(vctCard.size())){}

GameDeck::~GameDeck(){}

vector<Card> GameDeck::getDeck(){
	return myDeck;
}

int GameDeck::getNbrCard(){
	return cardsLeftInDeck;
}

Card GameDeck::giveCard(){
	int pos = rand() % getNbrCard();
	Card myCard = myDeck[pos];
	myDeck.erase(myDeck.begin()+pos);
	--cardsLeftInDeck;
	return myCard;
}