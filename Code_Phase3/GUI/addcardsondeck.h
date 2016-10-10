#ifndef ADDCARDSONDECK_H
#define ADDCARDSONDECK_H

#include <QDialog>
#include "client.h"

//#include "seedeck.h"

namespace Ui {
class AddCardsOnDeck;
}

class AddCardsOnDeck : public QDialog
{
    Q_OBJECT

public:
    explicit AddCardsOnDeck(QWidget *parent = 0);
    explicit AddCardsOnDeck(Client* myCl,int deck, QWidget *parent = 0);
    void setWdeck(int);
    int getWdeck();
    ~AddCardsOnDeck();

private slots:
    void on_validerButton_clicked();

    void on_quitterButton_clicked();

    void on_addButton_clicked();
    //----------------------------
    void addMyWidg(QWidget*);
    void removeMyWidg();
    void setMyRound();
    void closeEvent(QCloseEvent *bar);
    //void on_SeeButton_clicked();


signals:
    void closeAddCardSignal();



private:
    Ui::AddCardsOnDeck *ui;
    Client *myClient;
    //SeeDeck *sd;
    QWidget* myWidg = nullptr;
    int myRound = 0;
    int wDeck;
    bool modified =false;
};

#endif // ADDCARDSONDECK_H
