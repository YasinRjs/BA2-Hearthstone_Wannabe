#include "decktomodify.h"
#include "ui_decktomodify.h"
#include "client.h"
#include <QMessageBox>


DeckToModify::DeckToModify(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckToModify)
{
    ui->setupUi(this);
}

DeckToModify::DeckToModify(Client* myCl,CollectionMenuDialog* cm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeckToModify),
    myClient(myCl),
    collecMenu(cm)
{
    ui->setupUi(this);
    loadDecks();
}

void DeckToModify::on_lancerButton_clicked()
{
    QString txt = ui->chosenDeck->text();
    string txtString = txt.toStdString();
    if (stoi(txtString) > 0 && stoi(txtString) <= 5){
        viewOneDeck *vod = new viewOneDeck(myClient,stoi(txtString)-1,collecMenu);
        QObject::connect(vod, SIGNAL(closeOneDeckSignal()),this, SLOT(closeOneDeck()));

        //myClient->sendStringToServer("1");

        hide();

       // myClient->sendStringToServer("1");

        vod->show();
    }
    else{
        QMessageBox::information(this,tr("Choix du deck"),
        tr("Ce numero de deck est invalide !"));
    }
}


void DeckToModify::loadDecks(){
    QHBoxLayout* list[5][3];
    list[0][0] = ui->up1;
    list[0][1] = ui->mid1;
    list[0][2] = ui->down1;
    list[1][0] = ui->up2;
    list[1][1] = ui->mid2;
    list[1][2] = ui->down2;
    list[2][0] = ui->up3;
    list[2][1] = ui->mid3;
    list[2][2] = ui->down3;
    list[3][0] = ui->up4;
    list[3][1] = ui->mid4;
    list[3][2] = ui->down4;
    list[4][0] = ui->up5;
    list[4][1] = ui->mid5;
    list[4][2] = ui->down5;

    int deckSize;
    string parsedCard;
    for (int i=0;i<5;++i){
        deckSize = myClient->getDeck(i).getSize();
        myClient->sendStringToServer(to_string(deckSize));
        for (int j=0;j<deckSize;++j){
            myClient->sendStringToServer(to_string(myClient->getDeck(i).getCard(j)));
            myClient->receiveFromServer();
            parsedCard = myClient->getMsgServer();
            if (j<7){
                list[i][0]->addWidget(new GraphicalCard(this,parsedCard));
            }
            else if (j<14){
                list[i][1]->addWidget(new GraphicalCard(this,parsedCard));
            }
            else{
                list[i][2]->addWidget(new GraphicalCard(this,parsedCard));
            }
        }
    }
}


void DeckToModify::closeEvent(QCloseEvent *bar){
   myClient->sendStringToServer("collectionMenu");
    emit closeDeckToModifySignal();
}



DeckToModify::~DeckToModify()
{
    delete ui;
}


void DeckToModify::closeOneDeck(){
    delete vod;
    vod = nullptr;
    emit closeDeckToModifySignal();

}

