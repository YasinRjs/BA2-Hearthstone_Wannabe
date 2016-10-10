#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "card.hpp"

class AbstractCharacter: public Card {

public:
    AbstractCharacter();
    int receiveDamage(int);
};

#endif // CHARACTER_HPP
