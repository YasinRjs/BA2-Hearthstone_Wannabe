#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Card.hpp"

class AbstractCharacter: public Card {

public:
    AbstractCharacter();
    int receiveDamage(int);
};

#endif // CHARACTER_H_