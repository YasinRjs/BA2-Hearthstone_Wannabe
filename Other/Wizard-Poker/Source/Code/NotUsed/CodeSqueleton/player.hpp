#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>
#include "card.hpp"
#include "deck.hpp"

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
    QString name;
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

#endif // PLAYER_HPP
