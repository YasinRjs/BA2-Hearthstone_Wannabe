#ifndef VIEWONEDECK_H
#define VIEWONEDECK_H
#include "client.h"
#include <QDialog>
#include <vector>
#include "graphicalcard.h"
#include "addcardsondeck.h"

class CollectionMenuDialog;

namespace Ui {
class viewOneDeck;
}

class viewOneDeck : public QDialog
{
    Q_OBJECT

public:
    explicit viewOneDeck(QWidget *parent = 0);
    explicit viewOneDeck(Client* myCl,int deck,CollectionMenuDialog* cm, QWidget *parent = 0);
    void showDeck();
    void setWdeck(int);
    int getWdeck();

    ~viewOneDeck();

private:
    Ui::viewOneDeck *ui;
    Client* myClient;
    AddCardsOnDeck *addCard = nullptr;
    CollectionMenuDialog* collecMenu;

    vector<string> allCards;

    int wDeck;

signals:
    void closeOneDeckSignal();



private slots:
    void closeAddCard();
    void closeEvent(QCloseEvent *bar);
    void on_removeCardButton_clicked();
    void on_pushButton_clicked();
};

#endif // VIEWONEDECK_H
