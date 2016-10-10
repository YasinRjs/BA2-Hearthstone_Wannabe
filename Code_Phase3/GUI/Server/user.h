#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User {
    string _id;
    string _username;
    int _victory;
    int _defeat;
public:
    User();
    User(string, string, int, int);
    ~User();

    string getId();
    string getUsername();
    int getVictory();
    int getDefeat();
    int getRatio();

    void incVictory();
    void incDefeat();

    string getProfil();
};

#endif // USER_H