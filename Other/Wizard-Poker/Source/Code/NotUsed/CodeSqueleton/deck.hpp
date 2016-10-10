#ifndef DECK_HPP
#define DECK_HPP

#include "card.hpp"

class Deck
{
private:
    Card contents[];

public:
    Deck();
    ~Deck();
    int modifyDeck();
    int removeDeck();
    int copyDeck();
};

#endif // DECK_HPP
