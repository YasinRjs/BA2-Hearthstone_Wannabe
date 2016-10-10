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
    int hasUserNamed(string user){
      int i = 0;
      while (i<_numberUsers){
        if (user == _users[i]){
          return 1;
        }
        ++i;
      }
      return 0;
    }
    int getID(string user){
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
    int isCorrectPassword(int indice,char* pwd){
      return (!strcmp(pwd,_passwords[indice].c_str()));
    }

    void onlyForHackers(){
      int i=0;
      cout << "----- System got hacked -----" << endl;
      while (!(_users[i] == "")){
        cout << _users[i] << " : " << _passwords[i] << endl;
        ++i;
      }
      cout << "-----------------------------" << endl;
    }
    
    Database() : _numberUsers(0){
      ifstream fichier("comptes.txt");
      while (!fichier.eof()){
        //A chaque fois, si on est pas à la fin, on prends le nom ensuite le mdp
        getline(fichier,_users[_numberUsers]);
        getline(fichier,_passwords[_numberUsers]);
        addOneUser(); 
      }
      onlyForHackers();
    }
};
