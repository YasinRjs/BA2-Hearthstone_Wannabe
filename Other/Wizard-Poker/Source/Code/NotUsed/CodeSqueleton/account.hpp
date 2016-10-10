#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <QObject>

class Account
{
private:
    QString mail;
    QString password;
    Account friends[];
    Deck decklist[];
    Deck activeDeck;
    int victories;
    int defeats;
    // Card collection[]


public:
    Account();
    ~Account();
    int modifyProfile();
    int modifyDecks();
    int accesCollection(); // Called on open collection button in GUI
    int checkProfile();
};

#endif // ACCOUNT_HPP
