#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
}

mainMenu::mainMenu(Client *myCl,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu),
    myClient(myCl)
{
    ui->setupUi(this);
    friendsList = new FriendsList(myClient);
    startReception();
    adVector.push_back(QPixmap(":/img/img/ad1.jpg"));
    adVector.push_back(QPixmap(":/img/img/ad2.jpg"));
    adVector.push_back(QPixmap(":/img/img/ad3.jpg"));
    adVector.push_back(QPixmap(":/img/img/ad4.png"));
    adVector.push_back(QPixmap(":/img/img/ad5.png"));
    adVector.push_back(QPixmap(":/img/img/ad6.png"));
    adVector.push_back(QPixmap(":/img/img/ad7.jpg"));
    startAds();

}

mainMenu::~mainMenu()
{
    delete ui;
}


void mainMenu::on_pushButton_5_clicked()
{
    myClient->sendStringToServer("5");
    exit(0);
}

void mainMenu::on_pushButton_2_clicked()
{
    hide();
    collection = new CollectionMenuDialog(myClient, adVector);
    QObject::connect(collection, SIGNAL(closeCollectionSignal()),this, SLOT(closeCollection()));
    collection->show();
}

void mainMenu::on_pushButton_4_clicked()
{
    hide();
    myClient->sendStringToServer("4");
    myClient->receiveFromServer();  //reception du classement par le client en chaine de caractères.
    ranking = new RankingView(myClient);
    QObject::connect(ranking, SIGNAL(closeRankingSignal()),this, SLOT(closeRanking()));
    ranking->show();
}

void mainMenu::on_duelButton_clicked()
{
    hide();
    myClient->sendStringToServer("1");
    DuelWindow* duelPtr = new DuelWindow(myClient, friendsList, adVector);
    QObject::connect(duelPtr, SIGNAL(endSignal()),this, SLOT(finishGame()));
    // important, permet à deux objets de communiquer ensemble afin d'éviter les problèmes d'includes
    // Voir Jacky pour plus d'explication détaillés

    choseDeckDial = new choseDeckDialog(myClient, duelPtr);
    QObject::connect(choseDeckDial, SIGNAL(closeChoseDeckSignal()),this, SLOT(finishGame()));
    choseDeckDial->show();

}


void mainMenu::on_chatButton_clicked()
{
    friendsList->setFriendsList();
    friendsList->show();
}

void* receiveChatGUI(void* arg){
    FriendsList* friendsPtr = reinterpret_cast<FriendsList*>(arg);
    friendsPtr->chatReception();
    exit(0);

}

void mainMenu::startReception(){
    pthread_create(&chatThread,nullptr,receiveChatGUI,reinterpret_cast<void*>(friendsList));
}

void mainMenu::closeEvent(QCloseEvent *bar) // lorsqu'on ferme la fenêtre
{
    exit(0);
}

void mainMenu::finishGame(){
    delete choseDeckDial;
    choseDeckDial = nullptr;
    show();
}

void mainMenu::closeCollection(){
    delete collection;
    collection = nullptr;
    show();
}

void mainMenu::closeRanking(){
    delete ranking;
    ranking = nullptr;
    show();
}

void* adsManagerMainMenu(void* arg){
    mainMenu* menuPtr = reinterpret_cast<mainMenu*>(arg);
    menuPtr->adsManagement();
    pthread_exit(0);
}

void mainMenu::startAds(){
    pthread_create(&adsThread, nullptr, adsManagerMainMenu,reinterpret_cast<void*>(this));
}

void mainMenu::changeAd(int i){
    ui->pub->clear();
    ui->pub->setPixmap(adVector[i]);
}



void mainMenu::adsManagement(){
    QObject::connect(this, SIGNAL(changeAdSignal(int)),this, SLOT(changeAd(int)));

    while(1){
        for (int i=0; i < 7; ++i){
            emit changeAdSignal(i);
            sleep(7);
        }
    }
}
