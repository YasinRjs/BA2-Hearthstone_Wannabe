#include "collection.h"

using namespace std;

Collection::Collection() : nbrCards(0),allCards(vector<int>()){}

Collection::Collection(vector<int> mycollection): nbrCards(0),allCards(vector<int>()){
    size_t j = mycollection.size();
    for(size_t i=0;i<j;++i){
        addCardToCollection(mycollection[i]);
        nbrCards += 1;
    }
}

void Collection::addRandomCardToCollection(){
    nbrCards += 1;
    int id = getNewCardId();
    allCards.push_back(id);
}

void Collection::addCardToCollection(int ID){
    allCards.push_back(ID);
}

void Collection::replaceCardToNewCard(int victimeIndex){
    int id = getNewCardId();
    allCards[victimeIndex] = id;
}

int Collection::getNewCardId(){
    int newCardID = rand() % databaseIdRange;
    return newCardID;
}

void Collection::printCollection(){
    for(int i=0;i<nbrCards;++i){
        cout << allCards[i];
        if (i+1<nbrCards){
            cout <<",";
        }
    }
    cout << endl;
}

int Collection::getNbrCards(){
    return nbrCards;
}

int Collection::hasID(int ID){
    int found = 0;
    int i = 0;
    while (!found && i < getNbrCards()){
        if (allCards[i] == ID){
            found = 1;
        }
        ++i;
    }
    return found;
}

vector<int> Collection::getAllCards(){
    return allCards;
}

int Collection::getCard(int indice){
    return allCards[indice];
}
