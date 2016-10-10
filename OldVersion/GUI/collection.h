#ifndef COLLECTION_H
#define COLLECTION_H

#define databaseIdRange 200   // 200 cartes dans la database
#define CARDSWHENSIGNUP 100   // 100 cartes reçu à la création

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Collection{
//    void updateVariables();
//    void chooseVictime();
    int nbrCards;
    vector<int> allCards;
public:
    void addRandomCardToCollection();
    void addCardToCollection(int);
    void replaceCardToNewCard(int);
    void printCollection();
    int getNewCardId();
    int hasID(int);
    int getNbrCards();
    int getCard(int);
    vector<int> getAllCards();
//    void tributeCardToGetNew();

    Collection();
    Collection(vector<int>);
    ~Collection(){};

};

#endif // COLLECTION_H
