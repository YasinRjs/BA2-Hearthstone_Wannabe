#include "deck.h"

Deck::Deck() : myDeck(vector<int>()),nbrCards(20){
    myDeck.push_back(0);
}

Deck::Deck(vector<int> IDs):
    myDeck(IDs),nbrCards(20){}

Deck::~Deck(){}

int Deck::getSize(){
    return int(myDeck.size());
}

vector<int> Deck::giveDeck(){
    return myDeck;
}

void Deck::addCardinDeck(int ID){
    myDeck.push_back(ID);
    incrementNbrCards();
}

void Deck::incrementNbrCards(){
    ++nbrCards;
}

void Deck::printDeck(){
    cout <<"\t";
    for(int i=0;i<nbrCards;++i){
        cout << myDeck[i];
        if (i+1<nbrCards){
            cout << ",";
        }
    }
}

void Deck::removeDeck()
{
    myDeck.clear();
    nbrCards = 0;
}

vector<int> Deck::getMyDeck(){
    return myDeck;
}

int Deck::getCard(int indice){
    return myDeck[indice];
}

bool Deck::isEmpty(){
    return myDeck.empty();
}
void Deck::removeCard(int position){
    nbrCards -= 1;
    myDeck.erase(myDeck.begin() + position);
}
