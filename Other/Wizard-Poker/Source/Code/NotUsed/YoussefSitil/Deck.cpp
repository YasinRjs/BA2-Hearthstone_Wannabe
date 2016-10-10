#include "Deck.hpp"

Deck::Deck(vector<int> IDs):
	myDeck(IDs),nbrCards(20){}

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


void Deck::removeDeck()
{
	myDeck.clear();
	nbrCards = 0;
}


/*
void Deck::copyDeck(Deck otherDeck){
	myDeck = otherDeck.contentDeck;
	nbrCards = other.cardsNumber;
}
*/