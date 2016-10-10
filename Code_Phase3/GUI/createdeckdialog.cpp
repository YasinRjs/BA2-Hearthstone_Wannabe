#include "createdeckdialog.h"
#include "ui_createdeckdialog.h"
#include "graphicalcard.h"

CreateDeckDialog::CreateDeckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDeckDialog)
{
    ui->setupUi(this);
}

CreateDeckDialog::CreateDeckDialog(Client* myCl, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDeckDialog),
    myClient(myCl)
{
    ui->setupUi(this);
    collectionView();
}

CreateDeckDialog::~CreateDeckDialog()
{
    delete ui;
}

void CreateDeckDialog::on_addButton_clicked() {
    QString id = ui->cardID->text();
    string idStr = id.toStdString();
    if(vectId.size() < DECKSIZE) {
        if (stoi(idStr) < 0 || stoi(idStr) > 99) {
            QMessageBox::information(this,tr("Voir une carte"),
            tr("Vous ne possedez pas cette carte dans votre collection !"));
        }
        else {
            if(myClient->canPutInDeck(vectId, stoi(idStr))) {
                vectId.push_back(stoi(idStr));
                ui->cardID->setText("");
                QString labelTemplate = tr("<font style=font-size:14pt; color=#ffffff><b>%1</b></font>");
                ui->nbrOfCardsLabel->setText(labelTemplate.arg(QString::number(vectId.size())));
            }
            else {
                QMessageBox::information(this,tr("Erreur ajout"),
                tr("Vous ne pouvez pas avoir plus de 2 cartes identiques!\nVous ne pouvez pas ajouter une carte que vous de disposez pas!"));
            }
        }
    }
    else {
        QMessageBox::information(this,tr("Deck Remplis"),
        tr("Le deck est remplis. Veuillez valider ce dernier."));
    }
}

void CreateDeckDialog::on_validateButton_clicked() {
    if(vectId.size() == DECKSIZE) {
        myClient->sendStringToServer("2");
        myClient->receiveFromServer();
        myClient->sendStringToServer("4");
        myClient->createNewDeckFromVector(vectId, myClient->getUsername());
        close();
    }
    else {
        QMessageBox::information(this,tr("Création incomplète"),
        tr("Le deck n'est pas encore rempli.\nIl faut un total de 20 cartes pour la création d'un deck."));
    }
}

void CreateDeckDialog::collectionView(){
    QHBoxLayout* list[20];
    list[0] = ui->upF;
    list[1] = ui->downF;
    list[2] = ui->upS;
    list[3] = ui->downS;
    list[4] = ui->upT;
    list[5] = ui->downT;
    list[6] = ui->upFo;
    list[7] = ui->downFo;
    list[8] = ui->upFi;
    list[9] = ui->downFi;
    list[10] = ui->upSix;
    list[11] = ui->downSix;
    list[12] = ui->upSeven;
    list[13] = ui->downSeven;
    list[14] = ui->upE;
    list[15] = ui->downE;
    list[16] = ui->upN;
    list[17] = ui->downN;
    list[18] = ui->upTen;
    list[19] = ui->downTen;
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("1");
    myClient->receiveFromServer();
    int indice;
    int id;
    string parsedCard;
    for(int i=0;i<100;++i){
        indice = 0;
        id = myClient->getCollection().getCard(i);
        myClient->sendStringToServer(to_string(id));
        myClient->receiveFromServer();
        parsedCard = myClient->getMsgServer();
        while(i+1-(5*(indice+1)) > 0){
            indice += 1;
        }
        GraphicalCard *card = new GraphicalCard(this, parsedCard);
        card->changeId(i);
        list[indice]->addWidget(card);
    }
}

void CreateDeckDialog::closeEvent(QCloseEvent *bar){
    emit closeCreateDeckSignal();
}

void CreateDeckDialog::on_exitButton_clicked() {
    close();
}
