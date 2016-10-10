#include "database.h"

Database::Database() : _numberUsers(0),myCardDatabase(nullptr){}

Database::Database(CardDatabase* cardDB) : _numberUsers(0),myCardDatabase(cardDB) {
    getAccountsFromFile();
    onlyForHackers();
}

Database& Database::operator=(const Database&){
    return *this;
}

Database::Database(const Database&) : _numberUsers(0),myCardDatabase(nullptr) {}

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

int Database::getNbrUsers(){
    return _numberUsers;
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
        cout << "\tVictory : " << _victory[i] << endl;
        cout << "\tDefeat : " << _defeat[i] << endl;
        ++i;
    }
    cout << "-----------------------------" << endl;
}

void Database::addUser(string username,string password){
    _users[_numberUsers] = username;
    _passwords[_numberUsers] = password;
    _victory[_numberUsers] = 0;
    _defeat[_numberUsers] = 0;
    ++_numberUsers;
    //Write in file
    fstream fichier;
    //Critical
    fichier.open("../txt/comptes.txt",ios::app);
    fichier << username << endl;
    fichier << password << endl;
    fichier << "0" << endl;
    fichier << "0" << endl;
    fichier.close();
    fichier.open("../txt/comptesCollection.txt",ios::app);
    for(int i=0;i<100;++i){
        fichier << i;
        if (i+1<100){
            fichier << ",";
        }
    }
    fichier << endl;
    fichier.close();
    //Critical
}

void Database::getAccountsFromFile(){
    fstream fichier;
    fichier.open("../txt/comptes.txt");
    //Critical
    while (!fichier.eof()){
        string test;
        int value;
        getline(fichier,test);
        //Le test permet de ne pas ajouter la ligne de terminaison qui est vide
        if (test.size() > 0){
            _users[_numberUsers] = test;
            getline(fichier,_passwords[_numberUsers]);
            getline(fichier,test);
            value = atoi(test.c_str());
            _victory[_numberUsers] = value;
            getline(fichier,test);
            value = atoi(test.c_str());
            _defeat[_numberUsers] = value;
            addOneUser();
        }
    }
    fichier.close();
    //Critical
}

int Database::getVictory(int ID){
    return _victory[ID];
}

int Database::getDefeat(int ID){
    return _defeat[ID];
}

string Database::getUsername(int ID){
    return _users[ID];
}
