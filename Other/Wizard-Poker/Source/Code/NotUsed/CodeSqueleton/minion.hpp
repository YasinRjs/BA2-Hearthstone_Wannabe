#ifndef MINION_HPP
#define MINION_HPP

#include "character.hpp"

class Minion : public AbstractCharacter
{
private:
    int hp;
    int attack;
public:
    Minion();
    int attackThat(AbstractCharacter); // returns if minion dead or alive
};

#endif // MINION_HPP
