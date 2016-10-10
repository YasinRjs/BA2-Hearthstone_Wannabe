#include "collectionmenudialog.h"
#include "ui_collectionmenudialog.h"

CollectionMenuDialog::CollectionMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionMenuDialog)
{
    ui->setupUi(this);
}

CollectionMenuDialog::CollectionMenuDialog(Client* myCl,vector<QPixmap> ads, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionMenuDialog),
    myClient(myCl),
    adVector(ads)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    startAds();
}

CollectionMenuDialog::~CollectionMenuDialog()
{
    delete ui;
}

void CollectionMenuDialog::on_mainMenuButton_clicked()
{
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("7");
    close();
}

void CollectionMenuDialog::on_viewCollectionButton_clicked()
{
    hide();
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("1");
    myClient->receiveFromServer();
    collecGui = new CollectionGUI(myClient,this);
    QObject::connect(collecGui, SIGNAL(closeCollecGuiSignal()),this, SLOT(closeCollecGui()));
    collecGui->show();
}

void CollectionMenuDialog::on_viewCardButton_clicked()
{
    hide();
    oneCard = new OneCardDialog(myClient);
    QObject::connect(oneCard, SIGNAL(closeOneCardSignal()),this, SLOT(closeOneCard()));
    oneCard->show();

}

void CollectionMenuDialog::on_viewDecksButton_clicked()
{
    hide();
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();
    viewDeck = new viewDecksDialog(myClient);
    QObject::connect(viewDeck, SIGNAL(closeViewDeckSignal()),this, SLOT(closeViewDeck()));
    viewDeck->show();
}

void CollectionMenuDialog::on_createDeckButton_clicked()
{
    if (myClient->numberOfDecksFilled() == NUMBEROFDECK){
        QMessageBox::information(this,tr("Echec Création"),
        tr("Les 5 decks sont remplis.\nSupprimez en un pour en créer un nouveau."));
    }
    else{
        hide();
        createDeck = new CreateDeckDialog(myClient);
        QObject::connect(createDeck, SIGNAL(closeCreateDeckSignal()),this, SLOT(closeCreateDeck()));
        createDeck->show();
    }
}

void CollectionMenuDialog::on_deleteDeckButton_clicked()
{
    if (myClient->numberOfDecksFilled() == 1){
        QMessageBox::information(this,tr("Echec Création"),
        tr("Suppression impossible.\nVous devez avoir au moins un deck rempli."));
    }
    else{
    hide();
    deleteDeck = new DeleteDeckDialog(myClient);
    QObject::connect(deleteDeck, SIGNAL(closeDeleteDeckSignal()),this, SLOT(closeDeleteDeck()));
    deleteDeck->show();
    }
}

void CollectionMenuDialog::on_modifyDeckButton_clicked()
{
    hide();
    myClient->sendStringToServer("2");
    myClient->receiveFromServer();

    myClient->sendStringToServer("6");
    myClient->receiveFromServer();

    whichDeck = new DeckToModify(myClient,this);
    QObject::connect(whichDeck, SIGNAL(closeDeckToModifySignal()),this, SLOT(closeDeckToModify()));
    whichDeck->show();
}





void CollectionMenuDialog::closeEvent(QCloseEvent *bar){
    pthread_cancel(adsThread);
    emit closeCollectionSignal();
}

void CollectionMenuDialog::closeCollecGui(){
    delete collecGui;
    collecGui = nullptr;
    show();
}

void CollectionMenuDialog::closeOneCard(){
    delete oneCard;
    oneCard = nullptr;
    show();
}

void CollectionMenuDialog::closeViewDeck(){
    delete viewDeck;
    viewDeck = nullptr;
    show();
}

void CollectionMenuDialog::closeCreateDeck(){
    delete createDeck;
    createDeck = nullptr;
    show();
}

void CollectionMenuDialog::closeDeleteDeck(){
    delete deleteDeck;
    deleteDeck = nullptr;
    show();
}

void* adsManagerCollecMenu(void* arg){
    CollectionMenuDialog* menuPtr = reinterpret_cast<CollectionMenuDialog*>(arg);
    menuPtr->adsManagement();
    pthread_exit(0);
}

void CollectionMenuDialog::startAds(){
    pthread_create(&adsThread, nullptr, adsManagerCollecMenu,reinterpret_cast<void*>(this));
}

void CollectionMenuDialog::changeAd(int i){
    ui->pub->clear();
    ui->pub->setPixmap(adVector[i]);
}



void CollectionMenuDialog::adsManagement(){
    QObject::connect(this, SIGNAL(changeAdSignal(int)),this, SLOT(changeAd(int)));

    while(1){
        for (int i=0; i < 7; ++i){
            emit changeAdSignal(6-i);
            sleep(7);           
        }
    }
}

void CollectionMenuDialog::closeDeckToModify(){
    delete whichDeck;
    whichDeck = nullptr;
    show();
}
