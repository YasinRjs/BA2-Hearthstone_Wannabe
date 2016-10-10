#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Database{
	string _users[100];
	string _passwords[100];
	int _numberUsers;
public:
	void addOneUser(){
		++_numberUsers;
	}
	int hasUserNamed(string user);
	int getID(string user);
	int isCorrectPassword(int indice,char* pwd);
	void onlyForHackers();	
	void addUser(string username,string password);
	void getAccountsFromFile();

	Database() : _numberUsers(0){
		getAccountsFromFile();
		onlyForHackers();
	}
};


int Database::hasUserNamed(string user){
	int i = 0;
	while (i<_numberUsers){
		if (user == _users[i]){
			return 1;
		}
		++i;
	}
	return 0;
}

int Database::getID(string user){
	//Sera appelé que si on a déjà vérifié hasUserNamed
	int i=0;
	while (i<_numberUsers){
		if (user == _users[i]){
			return i;
		}
		++i;
	}
	return 0;
}

int Database::isCorrectPassword(int indice,char* pwd){
	return (!strcmp(pwd,_passwords[indice].c_str()));
}

void Database::onlyForHackers(){
	int i=0;
	cout << "~~~~~ System got hacked ~~~~~" << endl;
	while (i<_numberUsers){
		cout << _users[i] << " : " << _passwords[i] << endl;
		++i;
	}
	cout << "-----------------------------" << endl;
}

void Database::addUser(string username,string password){
	_users[_numberUsers] = username;
	_passwords[_numberUsers] = password;
	++_numberUsers;
	//Write in file
	fstream fichier;
	//Critical
	fichier.open("comptes.txt",ios::app);
	fichier << username << endl;
	fichier << password << endl;
	fichier.close();
	//Critical
}	

void Database::getAccountsFromFile(){
	fstream fichier;
	fichier.open("comptes.txt");
	//Critical
	while (!fichier.eof()){
		string test;
		getline(fichier,test);
		//Le test permet de ne pas ajouter la ligne de terminaison qui est vide
		if (test.size() > 0){
			_users[_numberUsers] = test;
			getline(fichier,_passwords[_numberUsers]);
			addOneUser(); 
		}
	}
	fichier.close();
	//Critical
}