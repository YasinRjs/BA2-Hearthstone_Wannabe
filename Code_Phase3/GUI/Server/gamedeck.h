#ifndef GAMEDECK_H
#define GAMEDECK_H

using namespace std;

#include "card.h"
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

#endif // GAMEDECK_H
