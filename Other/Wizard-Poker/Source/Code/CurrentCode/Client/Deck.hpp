#ifndef DECK_HPP_
#define DECK_HPP_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define cardsPerDeck 20

using namespace std;

class Deck{
    vector<int> myDeck;
    int nbrCards;
public:
//    void modifyDeck(int index,int newCardId);
    void removeDeck();
    void printDeck();
    void addCardinDeck(int);
    void incrementNbrCards();
	vector<int> giveDeck();
    vector<int> getMyDeck();	
//	void CopyDeck();
//	bool checkHowMuch(int);
    Deck();
	Deck(vector<int> IDs);
	~Deck();
};

#endif // DECK_HPP_
