#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Database{
	string users[100];
	string passwords[100];
	int numberUsers;
public:
	void addOneUser(){
		++numberUsers;
	}
	int hasUserNamed(string user);
	int getID(string user);
	int isCorrectPassword(int indice,char* pwd);
	void onlyForHackers();	
	void addUser(string username,string password);
	void getAccountsFromFile();

	Database() : numberUsers(0){
		getAccountsFromFile();
	}
};


int Database::hasUserNamed(string user){
	cout << "name : " << user << endl;
	int i = 0;
	while (i<numberUsers){
		if (user == users[i]){
			return 1;
		}
		++i;
	}
	return 0;
}

int Database::getID(string user){
	//Sera appelé que si on a déjà vérifié hasUserNamed
	int i=0;
	while (i<numberUsers){
		if (user == users[i]){
			return i;
		}
		++i;
	}
	return 0;
}

int Database::isCorrectPassword(int indice,char* pwd){
	return (!strcmp(pwd,passwords[indice].cstr()));
}

void Database::onlyForHackers(){
	int i=0;
	cout << "~~~~~ System got hacked ~~~~~" << endl;
	while (i<numberUsers){
		cout << users[i] << " : " << passwords[i] << endl;
		++i;
	}
	cout << "-----------------------------" << endl;
}

void Database::addUser(string username,string password){
	users[numberUsers] = username;
	passwords[numberUsers] = password;
	++numberUsers;
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
			users[numberUsers] = test;
			getline(fichier,passwords[numberUsers]);
			addOneUser(); 
		}
	}
	fichier.close();
	//Critical
}