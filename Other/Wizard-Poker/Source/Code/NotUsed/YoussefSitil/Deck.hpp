#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include "Collection.h"

#define cardsPerDeck 20

class Deck{
public:
//    void modifyDeck(int index,int newCardId);
    void RemoveDeck();
//	void CopyDeck();
//	bool checkHowMuch(int);
	Deck(vector<int>);
private:
    vector<int> myDeck;
    int nbrCards;
};

#endif // DECK_H_INCLUDED
