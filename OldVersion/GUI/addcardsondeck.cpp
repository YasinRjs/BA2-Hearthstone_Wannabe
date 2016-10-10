#include "addcardsondeck.h"
#include "ui_addcardsondeck.h"
#include <QMessageBox>
#include "graphicalcard.h"

AddCardsOnDeck::AddCardsOnDeck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCardsOnDeck)
{
    ui->setupUi(this);
}

AddCardsOnDeck::AddCardsOnDeck(Client* myCl,int deck,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCardsOnDeck),
    myClient(myCl),
    wDeck(deck)
{
    ui->setupUi(this);
    setWdeck(deck);
    //sd = new SeeDeck(myClient);
}



AddCardsOnDeck::~AddCardsOnDeck()
{
    delete ui;
    //delete sd;
}

void AddCardsOnDeck::on_validerButton_clicked()
{
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    QString id = ui->cardID->text();
    string idStr = id.toStdString();
    if (stoi(idStr) < 0 || stoi(idStr) > 99){
        QMessageBox::information(this,tr("Voir une carte"),
        tr("Vous ne possedez pas cette carte dans votre collection !"));
    }
    else{
        if (myRound){
            removeMyWidg();
            setMyRound();
        }
        myClient->sendStringToServer(idStr);
        myClient->receiveFromServer();




        string parsedCard = myClient->getMsgServer();
        QWidget* myWidg = new GraphicalCard(this,parsedCard);
        ui->upF->addWidget(myWidg);
        addMyWidg(myWidg);
    }
}


void AddCardsOnDeck::removeMyWidg(){
    ui->upF->removeWidget(myWidg);
}

void AddCardsOnDeck::addMyWidg(QWidget* widg){
    myRound = 1;
    myWidg = widg;
}

void AddCardsOnDeck::setMyRound(){
    myRound = 0;
}



void AddCardsOnDeck::on_quitterButton_clicked()
{
    close();
}

void AddCardsOnDeck::on_addButton_clicked()
{
    QString idCard =  ui->cardID->text();
    string txtString = idCard.toStdString();
    Deck deckToModify = myClient->getBufferDeck(wDeck);
    if (myClient->find(stoi(txtString),myClient->getCollection().getAllCards()) && deckToModify.getSize()<20 &&  myClient->count(stoi(txtString),deckToModify.getMyDeck()) < 2 ){
        if (myClient->find(stoi(txtString),deckToModify.getMyDeck())){
            if (myClient->count(stoi(txtString),myClient->getCollection().getAllCards())== 2){
                deckToModify.addCardinDeck(stoi(txtString));
                myClient->setBufferDeck(deckToModify,wDeck);
                deckToModify.printDeck();
                cout<<endl;
            }
            else{
                QMessageBox::information(this,tr("Ajouter une carte"),
                tr("Vous ne possedez pas cette carte 2 fois dans votre collection"));
            }
        }
        else{
            deckToModify.addCardinDeck(stoi(txtString));
            myClient->setBufferDeck(deckToModify,wDeck);
            deckToModify.printDeck();
            cout<<endl;
        }

    }
    else if (deckToModify.getSize() == 20){
            QMessageBox::information(this,tr("Ajouter une carte"),
            tr("Votre deck est remplie !"));
        }
    else if (!myClient->find(stoi(txtString),myClient->getCollection().getAllCards())){
        QMessageBox::information(this,tr("Ajouter une carte"),
        tr("Vous ne possedez pas cette carte dans votre collection"));
    }
    else if (myClient->count(stoi(txtString),deckToModify.getMyDeck()) == 2){
        QMessageBox::information(this,tr("Ajouter une carte"),
        tr("Vous avez votre carte déjà 2 fois dans votre deck"));

    }
}




void AddCardsOnDeck::closeEvent(QCloseEvent *bar){
    myClient->sendStringToServer("stop");
    emit closeAddCardSignal();
}
void AddCardsOnDeck::setWdeck(int newIndex){
    wDeck = newIndex;
}

int AddCardsOnDeck::getWdeck(){
    return wDeck;
}






/*
void AddCardsOnDeck::on_SeeButton_clicked()
{
    hide();
    myClient->sendStringToServer("3");
    sd->show();

}
*/
