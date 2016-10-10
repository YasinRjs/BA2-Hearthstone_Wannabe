#include "Card.hpp"

Card::Card() : canAttack(0),type(CardIdentity()){
}

Card::Card(string strings[], int values[]) : canAttack(0),type(CardIdentity()){
    string theName = strings[0];
    string desc = strings[1];
    int theId = values[0];
    int manaCost = values[1];
    int theAttack = values[2];
    int theHp = values[3];

    //this->type.artwork = ":/Images/"+theId+".jpg";
    type.description = desc;
    type.energyCost = manaCost;
    type.id = theId;
    type.name = theName;
    type.attack = theAttack;
    type.hp = theHp;
    //++Card::id;
}

Card::~Card(){}

void Card::disableAttack(){
    canAttack = 0;
}

void Card::enableAttack(){
    canAttack = 1;
}

int Card::isAbleToAttack(){
    return canAttack;
}

Card& Card::operator=(const Card& other) {
    type.description = other.type.description;
    type.energyCost = other.type.energyCost;
    type.id = other.type.id;
    type.name = other.type.name;
    type.attack = other.type.attack;
    type.hp = other.type.hp;
    return *this;
}

void Card::showCard(){
    cout << type.id << " : ";
    cout << type.name;
    cout << " ; Energie : ";
    cout << type.energyCost;
    cout << " ; Attaque,HP : ";
    cout << type.attack;
    cout <<",";
    cout << type.hp;
    cout << endl;
}

string Card::parseCard(){
    string card;
    card += type.name;
    card += " ; Energie : " + to_string(type.energyCost);
    card += " ; Attaque,Hp : " + to_string(type.attack) + "," + to_string(type.hp);
    card += "\n";
    return card;
}

int Card::getEnergyCost(){
    return type.energyCost;
}

string Card::getName(){
    return type.name;
}

int Card::getAttack(){
    return type.attack;
}

int Card::getHp(){
    return type.hp;
}

void Card::receiveDamage(int damage){
    type.hp -= damage;
}

int Card::isAlive(){
    return type.hp > 0 ? 1 : 0;
}