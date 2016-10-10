#ifndef COLLECTION_H_INCLUDED
#define COLLECTION_H_INCLUDED

#define databaseIdRange 200   // 200 cartes dans la database
#define CARDSWHENSINGUP 100   // 100 cartes reçu à la création

//LA COLLECTION VA ALLER DEMANDER AU SERVEUR, 
//LA COLLECTION DU JOUEURS QUI VA ETRE CHARGE PAR UN FICHIER TXT

#include "Card.hpp"
#include "Database.hpp"
#include <vector.h>

class Collection{
public:
    void addRandomCardToCollection();
    void addCardToCollection(int);
//    void tributeCardToGetNew();
    Collection();
private:
//    void updateVariables();
//    void chooseVictime();
//    void getNewCardId();
    int nbrCards;
    vector<int> allCards;
};

#endif // COLLECTION_H_INCLUDED
