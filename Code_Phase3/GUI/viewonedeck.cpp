#include "viewonedeck.h"
#include "ui_viewonedeck.h"
#include "deck.h"
//#include "graphicalcard.h"
#include <vector>
#include <QGridLayout>
#include <QMessageBox>
#include "collectionmenudialog.h"

viewOneDeck::viewOneDeck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewOneDeck)
{
    ui->setupUi(this);
}

viewOneDeck::viewOneDeck(Client* myCl,int deck,CollectionMenuDialog* cm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewOneDeck),
    myClient(myCl),
    collecMenu(cm),
    wDeck(deck)
{

    ui->setupUi(this);
    setWdeck(deck);
    showDeck();
    addCard = new AddCardsOnDeck(myClient,deck);

}



void viewOneDeck:: showDeck(){
    QHBoxLayout* list[1][3];
    list[0][0] = ui->up;
    list[0][1] = ui->mid;
    list[0][2] = ui->down;
    myClient->sendStringToServer("1");
    myClient->receiveFromServer();
    Deck deckToModify = myClient->getBufferDeck(wDeck);
    deckToModify.printDeck();
    cout<<deckToModify.getMyDeck().size()<<endl;
    myClient->sendStringToServer(to_string(deckToModify.getMyDeck().size()));
    myClient->receiveFromServer();//OK
    string parsedCard;
    for (size_t j=0;j<deckToModify.getMyDeck().size();++j){
            myClient->sendStringToServer(to_string(myClient->getBufferDeck(wDeck).getCard(j)));
            myClient->receiveFromServer();
            parsedCard = myClient->getMsgServer();
            allCards.push_back(parsedCard);

            GraphicalCard* myWidg =new GraphicalCard(this,parsedCard);


            if (j<7){
                list[0][0]->addWidget(myWidg);

            }
            else if (j<14){
                list[0][1]->addWidget(myWidg);

            }
            else{
                list[0][2]->addWidget(myWidg);

            }
    }



}

void viewOneDeck::closeEvent(QCloseEvent *bar){
    myClient->sendStringToServer("collectionMenu");
    emit closeOneDeckSignal();
}

viewOneDeck::~viewOneDeck()
{
    delete ui;
    delete addCard;
}




void viewOneDeck::on_removeCardButton_clicked()
{

    QString txt = ui->txt->text();
    string txtString = txt.toStdString();
    Deck deckToModify = myClient->getBufferDeck(wDeck);
    if (myClient->find(stoi(txtString),deckToModify.getMyDeck()) && deckToModify.getMyDeck().size() != 0 ){
        size_t position = myClient->positionOfAnElement(stoi(txtString),deckToModify.getMyDeck());

        deckToModify.removeCard(position);
        allCards.erase(allCards.begin()+position);
        deckToModify.printDeck();
        cout<<endl;

        myClient->setBufferDeck(deckToModify,wDeck);




        if ( ui->up->layout() != NULL ){
            QLayoutItem* item;
            while ( ( item = ui->up->layout()->takeAt(0)) != NULL ){
                delete item->widget();
                delete item;
            }
        }

        if ( ui->mid->layout() != NULL ){
            QLayoutItem* item;
            while ( ( item = ui->mid->layout()->takeAt(0)) != NULL ){
                delete item->widget();
                delete item;
            }
        }

        if ( ui->down->layout() != NULL ){
            QLayoutItem* item;
            while ( ( item = ui->down->layout()->takeAt(0)) != NULL ){
                delete item->widget();
                delete item;
            }
        }

        for (size_t j=0;j<allCards.size();++j){
            GraphicalCard* myWidg =new GraphicalCard(this,allCards[j]);
            if (j<7){
                    ui->up->addWidget(myWidg);
                }
                else if (j<14){
                    ui->mid->addWidget(myWidg);
                }
                else{
                     ui->down->addWidget(myWidg);
                }
        }


    }
    else {
        if (deckToModify.getMyDeck().size() == 0){

            QMessageBox::information(this,tr("Choix de la carte à supprimer"),
            tr("Le deck est déjà vide !"));

        }
        else if (!myClient->find(stoi(txtString),deckToModify.getMyDeck())){
            deckToModify.printDeck();
            cout<<endl;

            QMessageBox::information(this,tr("Choix de la carte à supprimer"),
            tr("L'id de la carte n'est pas valide !"));

        }


    }

}

void viewOneDeck::setWdeck(int newIndex){
    wDeck = newIndex;
}

int viewOneDeck::getWdeck(){
    return wDeck;
}



void viewOneDeck::on_pushButton_clicked()
{
    hide();
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    QObject::connect(addCard, SIGNAL(closeAddCardSignal()),this, SLOT(closeAddCard()));
    //addCard->ui->nbrOfCardsLabel->setText(labelTemplate.arg(QString::number(myClient->getBufferDeck(wDeck).getMyDeck().size())));
    addCard->show();
}


void viewOneDeck::closeAddCard(){
    delete addCard;
    addCard = nullptr;
    emit closeOneDeckSignal();
}




