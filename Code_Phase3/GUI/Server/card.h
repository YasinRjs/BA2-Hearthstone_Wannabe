#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

typedef struct CardIdentity {
    int id = -1;
    string name = "None";
    string description = "";
    int energyCost = 0;
    int attack = 0;
    int hp = 0;
    //string artwork; // Only necessary for interface
} CardIdentity;

class Card{

    int canAttack;
public:
    CardIdentity type;
    Card();
    Card(string[], int[]);
    ~Card();
    Card& operator=(const Card&);
    void showCard();
    int getEnergyCost();
    string parseCard();
    string getName();
    void enableAttack();
    void disableAttack();
    int isAbleToAttack();
    int getAttack();
    int getHp();
    void receiveDamage(int);
    int isAlive();
    string guiParseCard();
    string guiParserCard();
};


#endif // CARD_H
