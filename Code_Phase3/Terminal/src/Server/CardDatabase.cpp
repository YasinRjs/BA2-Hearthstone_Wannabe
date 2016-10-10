#include "CardDatabase.hpp"

CardDatabase::CardDatabase() : _numberCards(0){
    getCardsFromFile();
}

void CardDatabase::addOneCard(){
	++_numberCards;
}

int CardDatabase::getNbrCards() {
    return _numberCards;
}

int CardDatabase::hasCardNamed(string cardName){
	//Sera appelé que si on a déjà vérifié hasCardNamed
	int i=0;
	while (i<_numberCards){
		if (cardName == _cardNames[i]){
			return 1;
		}
		++i;
	}
	return 0;
}

int CardDatabase::getID(string cardName){
    int i=0;
	while (i<_numberCards){
		if (cardName == _cardNames[i]){
			return _cards[i].type.id;
		}
		++i;
	}
	return 0;
}

void CardDatabase::getCardsFromFile(){
    fstream fichier;
	fichier.open("src/txt/cards.txt");
	int id = 0;
	//Critical
	while (!fichier.eof()){
		string name;
		string buffer;
		string strings[2];
		int values[4];
		getline(fichier,name);
		//Le test permet de ne pas ajouter la ligne de terminaison qui est vide
		if (name.size() > 0){
            strings[0] = name;
            strings[1] = "";
            values[0] = id; // ID
			getline(fichier,buffer);
			values[1] = atoi(buffer.c_str()); // Cost
			getline(fichier,buffer);
			values[2] = atoi(buffer.c_str()); // Attack
			getline(fichier, buffer);
			values[3] = atoi(buffer.c_str()); // Hp
			_cards[id] = Card(strings, values);
			addOneCard();
			id++;
		}
	}
	fichier.close();
}

string CardDatabase::getName(int ID){
    return _cards[ID].type.name;
}

string CardDatabase::getDescription(int ID){
    return _cards[ID].type.description;
}

int CardDatabase::getAttack(int ID){
    return _cards[ID].type.attack;
}

int CardDatabase::getHp(int ID){
    return _cards[ID].type.hp;
}

int CardDatabase::getCost(int ID){
    return _cards[ID].type.energyCost;
}

int* CardDatabase::initialCards() {
    int* starter = new int[100];
    for(int i = 0; i < 100; i++) {
        starter[i] = i;
    }
    return starter;
}

Card CardDatabase::getCard(int ID){
	return _cards[ID];
}

void CardDatabase::showAllCards(){
	for(int i=0;i<_numberCards;++i){
		_cards[i].showCard();
	}
	cout << "---------------------------------------" << endl;
}

