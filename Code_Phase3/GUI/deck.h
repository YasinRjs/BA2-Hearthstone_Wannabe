#ifndef DECK_H
#define DECK_H

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
//  void modifyDeck(int index,int newCardId);
    void removeDeck();
    void printDeck();
    void addCardinDeck(int);
    void incrementNbrCards();
    vector<int> giveDeck();
    vector<int> getMyDeck();
    int getSize();
    int getCard(int);
    bool isEmpty();
//	void CopyDeck();
//	bool checkHowMuch(int);
    void removeCard(int);
    Deck();
    Deck(vector<int> IDs);
    ~Deck();
};

#endif // DECK_H
