#ifndef COLLECTION_HPP_
#define COLLECTION_HPP_

#define databaseIdRange 200   // 200 cartes dans la database
#define CARDSWHENSIGNUP 100   // 100 cartes reçu à la création

//LE CLIENT VA DEMANDER AU SERVEUR SA LISTE d'ID.
//QUI SERA DANS LE TXT database sous forme 1,2,10,50,...

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
    vector<int> getAllCards();
//    void tributeCardToGetNew();

    Collection();
    Collection(vector<int>);
    ~Collection(){};
};

#endif // COLLECTION_HPP_
