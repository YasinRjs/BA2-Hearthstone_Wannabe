#include "User.hpp"

User::User() : _id("-1"),_username("None"),_victory(0),_defeat(0){}

User::User(string id, string username, int v, int d) 
	: _id(id), _username(username), _victory(v), _defeat(d) {}

User::~User(){}

string User::getId() {
	return _id;
}

string User::getUsername() {
	return _username;
}

int User::getVictory() {
	return _victory;
}

int User::getDefeat() {
	return _defeat;
}

int User::getRatio() {
	return (_victory - _defeat);
}

void User::incVictory() {
	++_victory;
}

void User::incDefeat() {
	++_defeat;
}

string User::getProfil() {
	string profil;
	profil += ("\n\tUsername: " + _username);
	profil += ("\n\tVictory: " + to_string(_victory));
	profil += ("\n\tDefeat: " + to_string(_defeat));
	return profil;
}
