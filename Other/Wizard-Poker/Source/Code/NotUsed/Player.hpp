#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "card.hpp"
#include "deck.hpp"

using namespace std;

class Player
{
    /*  Buffer class between account and a duel.
     *  Player dies, account looses a game
     *  Given how this class will be ever present in socket functions,
     *  and server interactions, all methods will return an integer
     *  to show if succesfully completed or not.
     *
     */
private:
    // Attributes
    string name;
    Card hand[];
    Deck deck;
    int healthpoints;
    Player opponent;
    int maxEnergyAvailable;
    int turnEnergy;
    Card graveyard[]; // Minion
    Card battlefield[]; // Minion

    // Methods
    Card drawCard();
    int gainEnergy();
    int putInGraveyard(Card);
    int summon(Card); // Param: Minion

public:
    Player();
    ~Player();
    int receiveDamage(int);
    int win();
    int loose();
    int receiveEffect(); // Param: Effect
    int startNewTurn();
    int endTurn();

};

#endif // PLAYER_H_