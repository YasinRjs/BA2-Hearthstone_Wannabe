#include "player.hpp"

#define FAILURE 0
#define SUCCESS 1

Player::Player()
{
    // TODO
}

Player::startNewTurn() {
    if (hand.length < 10) hand += drawCard();
    else putInGraveyard(drawCard());
    if (maxEnergyAvailable < 10) maxEnergyAvailable++;
    turnEnergy = maxEnergyAvailable;
    return SUCCESS;
}

Player::summon(Card toSummon) {
    // assert Card is Minion
    if (battlefield.length < 5 && turnEnergy >= toSummon.type.energyCost ) {
        battlefield += toSummon;
        turnEnergy -= toSummon.type.energyCost;
        return SUCCESS;
    }
    return FAILURE;
}

