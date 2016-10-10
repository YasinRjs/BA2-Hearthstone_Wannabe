#include "Deck.hpp"

Deck::Deck() : myDeck(vector<int>()),nbrCards(20){
	myDeck.push_back(0);
}

Deck::Deck(vector<int> IDs):
	myDeck(IDs),nbrCards(20){}

Deck::~Deck(){}

/*void Deck::modifyDeck(int index,int newCardId){
	bool canModify = checkHowMuch(newCardId);
	if (canModify)
	{	
		contentDeck[index] = newCardId;
	}
}
*/

/*bool Deck::checkHowMuch(int cardId)
{
	bool result = false;
	int counting = 0;
	for(int i = 0; i < cardsNumber;++i)
	{
		if (contentDeck[i] == cardId)
		{
			counting += 1;
		}
	}
	if (!(counting >= 2))
	{
		result = true;
	}

	return result;
}
*/

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


/*
void Deck::copyDeck(Deck otherDeck){
	myDeck = otherDeck.contentDeck;
	nbrCards = other.cardsNumber;
}
*/
