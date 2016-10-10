#include "Collection.h"

using namespace std;

Collection::Collection():nbrCards(0){
	for(int i = 0; i < CARDSWHENSIGNUP; ++i)
	{
		addCardToCollection(i);
		nbrCards += 1;
	}
}

void Collection::addRandomCardToCollection()
{
    nbrCards += 1;
    getNewCardId(-1);
}

void Collection::addCardToCollection(int ID){
    allCards.push_back(ID);
}


void Collection::getNewCardId(int victimeIndex)
{
    // Ici on est sûr que l'attibut victimeIndex
    // n'est pas extravaguant car vérifié dans chooseVictime.
    srand(time(NULL));
    if (victimeIndex == -1)
    {
        int databaseId = rand() % databaseIdRange;
        allCards.push_back(databaseId);
    }
    else
    {
        int databaseId = rand() % databaseIdRange;
        allCards[victimeIndex] = databaseId;
    }
}

/*void Collection::tributeCardToGetNew()
{
    int victimeIndex;
    victimeIndex = chooseVictime();

    if (victimeIndex != -1)
    {
        getNewCardId(victimeIndex);
    }
}

void Collection::chooseVictime()
{
    int index;
    cout << "Veuillez entrer le numéro de la carte que vous voulez sacrifier (-1 pour ne rien faire): " << endl;
    cin >> index;

    if (index >= 0 && index < nbrCards)
    {
            return index;
    }
    else
    {
        return -1;
    }
}
*/