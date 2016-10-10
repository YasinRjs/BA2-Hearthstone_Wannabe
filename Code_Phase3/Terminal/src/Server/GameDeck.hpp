#ifndef GameDeck_HPP_
#define GameDeck_HPP_

using namespace std;

#include "Card.hpp"
#include <vector>
#include <string>

class GameDeck{
	vector<Card> myDeck;
	int cardsLeftInDeck;

public:
	GameDeck();
	GameDeck(vector<Card>);
	~GameDeck();

	vector<Card> getDeck();
	int getNbrCard();
	Card giveCard();
};

#endif  //GameDeck_HPP_