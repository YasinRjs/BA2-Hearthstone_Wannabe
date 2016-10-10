#ifndef Database_HPP_
#define Database_HPP_

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

#include "CardDatabase.hpp"

using namespace std;

class Database{
	string _users[200];
	string _passwords[200];
	int _victory[200];
	int _defeat[200];
	int _numberUsers;
	CardDatabase* myCardDatabase;

public:
	void addOneUser(){
		++_numberUsers;
	}
	int getVictory(int);
	int getDefeat(int);
	int getNbrUsers();
	int hasUserNamed(string);
	int getID(string);
	int isCorrectPassword(int,char*);
	void onlyForHackers();
	void addUser(string,string);
	void getAccountsFromFile();
//----------------------------
	string getUsername(int);

	Database();
	Database(CardDatabase*);
	Database(const Database&);
	Database& operator=(const Database&);
	~Database();
};

#endif /* Database_HPP_ */
