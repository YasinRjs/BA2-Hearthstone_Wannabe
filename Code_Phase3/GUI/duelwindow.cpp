#include "duelwindow.h"
#include "ui_duelwindow.h"

DuelWindow::DuelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuelWindow)
{
    ui->setupUi(this);
}

DuelWindow::DuelWindow(Client* myCl, FriendsList* fl,vector<QPixmap> ads, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuelWindow),
    myClient(myCl),
    friendslist(fl),        // TO YASIN QUAND LA GAME EST TERMINÉ, FAIRE APPEL A "emit endSignal()" pour suprimé les objets créés lors d'un lancement de partie
    adVector(ads),
    gameOver(0),
    canPlay(0),
    rounds(0)
{
    ui->setupUi(this);
    ui->ennemyBoard->
    QObject::connect(this, SIGNAL(threadBoxOpponentTurn()),this, SLOT(boxOpponentTurn()));
    QObject::connect(this, SIGNAL(threadBoxDefaite()),this, SLOT(boxDefaite()));
    QObject::connect(this, SIGNAL(threadBoxVictoire()),this, SLOT(boxVictoire()));
    QObject::connect(this, SIGNAL(threadBoxSurrender()),this, SLOT(boxSurrender()));
    QObject::connect(this, SIGNAL(threadBoxISurrender()),this, SLOT(boxISurrender()));
    QObject::connect(this, SIGNAL(threadBoxEndTurn()),this, SLOT(boxEndTurn()));
    QObject::connect(this, SIGNAL(threadStartTurn()),this, SLOT(startTurnTest()));
    QObject::connect(this, SIGNAL(threadBoxRageQuit()),this, SLOT(boxRageQuit()));
}

DuelWindow::~DuelWindow()
{
    delete ui;
}


void DuelWindow::startMatch(){
    gameOver = 0;
    canPlay = 0;
    rounds = 0;
    opponent = myClient->getMsgServer();
    startAds();
    startTurn();
}

void DuelWindow::startTurn(){
    myClient->receiveFromServer();
    myClient->sendConfirmation(myClient->getSockfd());	// Pour voir si le client est tjr co

    if (myClient->isMyTurn()){
        ui->turn->setText("C'est votre tour !");
        setCanPlay();
        myClient->receiveFromServer();  //Board();
        refreshBoard();
        myClient->sendStringToServer("OK");
        myClient->receiveFromServer();  //Hand();
        refreshHand();

        createWaitingThread();
    }
    else if (myClient->isWaitingTurn()){
        ui->turn->setText("Ce n'est pas votre tour !");
        cantPlay();
        myClient->receiveFromServer();  //Board();
        refreshBoard();
        myClient->sendStringToServer("OK");
        myClient->receiveFromServer();  //Hand();
        refreshHand();

        createWaitingThread();
    }
    if (!rounds){
        QMessageBox::information(this,tr("Adversaire trouve"),
        tr(opponent.c_str()));
        setRounds();
    }
}

void DuelWindow::startTurnTest(){
    startTurn();
}

void DuelWindow::setCanPlay(){
    canPlay = 1;
}

void DuelWindow::cantPlay(){
    canPlay = 0;
}

void DuelWindow::refreshHand(){
    if ( myCards.size() > 0 && ui->ownHand->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->ownHand->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
    string hand = myClient->getMsgServer();
    string token;
    string delimiter = "---";
    size_t pos = 0;
    GraphicalCard* card;
    myCards.clear();
    while ((pos = hand.find(delimiter)) != std::string::npos) {
        token = hand.substr(0, pos);
        hand.erase(0, pos + delimiter.length());
        card = new GraphicalCard(this,token);
        myCards.push_back(card);
        ui->ownHand->addWidget(card);
    }
    token = hand.substr(0,string::npos);
    card = new GraphicalCard(this,token);
    myCards.push_back(card);
    ui->ownHand->addWidget(card);
}

void DuelWindow::refreshBoard(){
    string board = myClient->getMsgServer();
    string delimeter = "---";

    size_t pos = 0;
    string token;
    pos = board.find(delimeter);
    token = board.substr(0,pos);
    board.erase(0, pos + delimeter.length());
    refreshEnnemyStat(token);

    pos = board.find(delimeter);
    token = board.substr(0,pos);
    board.erase(0, pos + delimeter.length());
    refreshEnnemyBoard(token);

    pos = board.find(delimeter);
    token = board.substr(0,pos);
    board.erase(0, pos + delimeter.length());
    refreshOwnBoard(token);

    pos = board.find(delimeter);
    token = board.substr(0,pos);
    board.erase(0, pos + delimeter.length());
    refreshOwnStat(token);
}

void DuelWindow::refreshOwnStat(string ownStat){
    size_t posToken = 0;
    string token;
    string delimeter = "_";

    posToken = ownStat.find(delimeter);
    token = ownStat.substr(0,posToken);
    ownStat.erase(0, posToken + delimeter.length());
    ui->ownName->setText("<strong>"+QString::fromStdString(token)+"</strong>");
    posToken = ownStat.find(delimeter);
    token = ownStat.substr(0,posToken);
    ownStat.erase(0, posToken + delimeter.length());
    ui->ownHp->setText("<strong>"+QString::fromStdString(token)+"</strong>");
    posToken = ownStat.find(delimeter);
    token = ownStat.substr(0,posToken);
    ui->ownEnergy->setText("<strong>"+QString::fromStdString(token)+"</strong>");
}

void DuelWindow::refreshEnnemyStat(string ennemyStat){
    size_t posToken = 0;
    string token;
    string delimeter = "_";

    posToken = ennemyStat.find(delimeter);
    token = ennemyStat.substr(0,posToken);
    ennemyStat.erase(0, posToken + delimeter.length());
    ui->ennemyName->setText(QString::fromStdString(token));
    posToken = ennemyStat.find(delimeter);
    token = ennemyStat.substr(0,posToken);
    ennemyStat.erase(0, posToken + delimeter.length());
    ui->ennemyHp->setText(QString::fromStdString(token));
    posToken = ennemyStat.find(delimeter);
    token = ennemyStat.substr(0,posToken);
    ui->ennemyEnergy->setText(QString::fromStdString(token));
}

void DuelWindow::refreshEnnemyBoard(string ennemyBoard){
    size_t pos = 0;
    string token;
    string delimeter = "_";
    string board = ennemyBoard;

    if ( ui->ennemyBoard->layout() != NULL ){
        QLayoutItem* item;
        while ( ( item = ui->ennemyBoard->layout()->takeAt(0)) != NULL ){
            delete item->widget();
            delete item;
        }
    }
    pos = board.find(delimeter);
    token = board.substr(0,pos);
    board.erase(0,pos+delimeter.length());
    GraphicalCard* card;
    while ((pos = board.find(delimeter)) != std::string::npos){
        token = board.substr(0,pos);
        board.erase(0, pos + delimeter.length());
        card = new GraphicalCard(this,token);
        ui->ennemyBoard->addWidget(card);
    }
    if ( board.size() > 4){
        token = board.substr(0,string::npos);
        card = new GraphicalCard(this,token);
        ui->ennemyBoard->addWidget(card);
    }
}

void DuelWindow::refreshOwnBoard(string ownBoard){
    size_t pos = 0;
    string token;
    string delimeter = "_";
    string board = ownBoard;
    if ( ui->ownBoard->layout() != NULL ){
        QLayoutItem* item;
        while ( ( item = ui->ownBoard->layout()->takeAt(0)) != NULL ){
            delete item->widget();
            delete item;
        }
    }
    pos = board.find(delimeter);
    token = board.substr(0,pos);
    board.erase(0,pos+delimeter.length());

    GraphicalCard* card;
    while ((pos = board.find(delimeter)) != std::string::npos){
        token = board.substr(0,pos);
        board.erase(0, pos + delimeter.length());
        card = new GraphicalCard(this,token);
        ui->ownBoard->addWidget(card);
    }
    if ( board.size() > 4){
        token = board.substr(0,string::npos);
        card = new GraphicalCard(this,token);
        ui->ownBoard->addWidget(card);
    }
}

void DuelWindow::on_finTourButton_clicked()
{
    if (canPlay){
        myClient->sendStringToServer("4");
    }
    else{
        QMessageBox::information(this,tr("Attention"),
        tr("Ce n'est pas votre tour !"));
    }
}


void DuelWindow::on_chatButton_clicked()
{
    friendslist->setFriendsList();
    friendslist->show();
}

void DuelWindow::setRounds(){
    rounds = 1;
}

Client* DuelWindow::getMyClient(){
    return myClient;
}

void DuelWindow::boxVictoire(){
    QMessageBox::information(this,tr("Victoire"),
    tr("Vous avez gagne par KO technique !"));
    pthread_cancel(adsThread);
    emit endSignal();
}

void DuelWindow::boxDefaite(){
    QMessageBox::information(this,tr("Defaite"),
    tr("Vous avez perdu par KO technique !"));
    pthread_cancel(adsThread);
    emit endSignal();
}

void DuelWindow::boxSurrender(){
    QMessageBox::information(this,tr("Victoire"),
    tr("Votre adversaire a abandonne !"));
    pthread_cancel(adsThread);
    emit endSignal();
}

void DuelWindow::boxEndTurn(){
    QMessageBox::information(this,tr("Fin de tour"),
    tr("C'est votre tour !"));
}

void DuelWindow::boxISurrender(){
    QMessageBox::information(this,tr("Abandon"),
    tr("Vous etes trop mauvais et abandonnez !"));
    pthread_cancel(adsThread);
    emit endSignal();
}

void DuelWindow::boxRageQuit(){
    QMessageBox::information(this,tr("RageQuit"),
    tr("AHAHA ! Votre adversaire a RageQuit !"));
    pthread_cancel(adsThread);
    emit endSignal();
}

void DuelWindow::boxOpponentTurn(){
    QMessageBox::information(this,tr("Fin de tour"),
    tr("C'est le tour de votre adversaire !"));
}

void DuelWindow::on_abandonButton_clicked()
{
    if (canPlay){
        myClient->sendStringToServer("5");
    }
    else{
        QMessageBox::information(this,tr("Attention"),
        tr("Ce n'est pas votre tour !"));
    }
}

void DuelWindow::closeEvent(QCloseEvent *bar) // lorsqu'on ferme la fenêtre
{
    if (canPlay && forceClose){
        myClient->sendStringToServer("Deconnection");
        exit(0);
    }
    if (!canPlay && forceClose){
        QMessageBox::information(this,tr("RageQuit condition"),
        tr("On attends la fin du tour de l'adversaire pour RageQuit !"));
        bar->ignore();
    }
}

void DuelWindow::on_jouerButton_clicked()
{
    if (canPlay){
        myClient->sendStringToServer("1");
        myClient->receiveFromServer();
        myClient->setHandSize(stoi(myClient->getMsgServer()));

        myClient->sendStringToServer("OK");
        myClient->receiveFromServer();
        //------------- recu hand
        PlayOneCardDialog playCardDia(myClient);
        playCardDia.setModal(true);
        playCardDia.exec();

    }
    else{
        QMessageBox::information(this,tr("Attention"),
        tr("Ce n'est pas votre tour !"));
    }
}


void DuelWindow::on_attaquerButton_clicked()
{
    if (canPlay){
        myClient->sendStringToServer("2");
        myClient->receiveFromServer();
        int nbrCanAtk = stoi(myClient->getMsgServer());
        if (nbrCanAtk > 0){
            myClient->setCanAtk(nbrCanAtk);

            myClient->receiveFromServer();
            CanAtkDialog canAtkDia(myClient);
            canAtkDia.setModal(true);
            canAtkDia.exec();
        }
        else{
            QMessageBox::information(this,tr("Attention"),
            tr("Vous n'avez pas de minion capable d'attaquer ce tour !"));
        }
    }
    else{
        QMessageBox::information(this,tr("Attention"),
        tr("Ce n'est pas votre tour !"));
    }
}

void DuelWindow::setNewTurn(int nbr){
    newTurn = nbr;
}

void* waitOpponent(void* arg){
    DuelWindow* myDuelWindow = reinterpret_cast<DuelWindow*>(arg);
    myDuelWindow->setNewTurn(0);
    myDuelWindow->getMyClient()->receiveFromGameSocket();
    string waitMsg = myDuelWindow->getMyClient()->getWaitMsg();

    //JACKY, REDIRIGER VERS MAIN WINDOW QUAND "lose","win","surrenderWin","surrenderLose","winRageQuit"
    if (waitMsg == "lose"){
        //winByKO
        //ICI PAR EXEMPLE, IL FAUT CLOSE CE WINDOW ET SHOW LE MAIN MENU
        myDuelWindow->setForceClose(0);
        emit myDuelWindow->threadBoxDefaite();
        //...
    }
    else if (waitMsg == "win"){
        myDuelWindow->setForceClose(0);
        emit myDuelWindow->threadBoxVictoire();
    }
    else if (waitMsg == "surrenderWin"){
        //Surrender
        myDuelWindow->setForceClose(0);
        emit myDuelWindow->threadBoxSurrender();
        //...
    }
    else if (waitMsg == "surrenderLose"){
        myDuelWindow->setForceClose(0);
        emit myDuelWindow->threadBoxISurrender();
    }
    else if (waitMsg == "winRageQuit"){
        myDuelWindow->setForceClose(0);
        emit myDuelWindow->threadBoxRageQuit();
    }
    else{
        //YourTurn
        if (waitMsg == "endTurn"){
            myDuelWindow->setNewTurn(1);
            emit myDuelWindow->threadBoxEndTurn();
        }
        //...
        emit myDuelWindow->threadStartTurn();
    }
    pthread_exit(0);
}

void DuelWindow::createWaitingThread(){
    pthread_create(&waitThread,nullptr,waitOpponent,reinterpret_cast<void*>(this));
}

void DuelWindow::setForceClose(int fc){
    forceClose = fc;
}





void* adsManagerDuelWindow(void* arg){
    DuelWindow* duelPtr = reinterpret_cast<DuelWindow*>(arg);
    duelPtr->adsManagement();
    pthread_exit(0);
}

void DuelWindow::startAds(){
    pthread_create(&adsThread, nullptr, adsManagerDuelWindow,reinterpret_cast<void*>(this));
}

void DuelWindow::changeAd(int i){
    ui->pub->clear();
    ui->pub->setPixmap(adVector[i]);
}



void DuelWindow::adsManagement(){
    QObject::connect(this, SIGNAL(changeAdSignal(int)),this, SLOT(changeAd(int)));

    while(1){
        for (int i=0; i < 7; ++i){
            emit changeAdSignal(6-i);
            sleep(7);       
        }
    }
}
