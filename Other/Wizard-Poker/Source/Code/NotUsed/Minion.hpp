#ifndef MINION_H_
#define MINION_H_

#include "Character.hpp"

class Minion : public AbstractCharacter
{
private:
    int hp;
    int attack;
public:
    Minion();
    int attackThat(AbstractCharacter); // returns if minion dead or alive
};

#endif // MINION_H_