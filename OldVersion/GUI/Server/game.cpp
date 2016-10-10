#include "game.h"

Game::Game() : myServer(nullptr),player1(nullptr),player2(nullptr),inProgress(1),numbytes(0),
num(0),currentPlayer(nullptr),waitingPlayer(nullptr),endTurn(0),gameOver(0),totalTurn(0){}

Game::Game(Server* server,Player* play1, Player* play2) : myServer(server),player1(play1), player2(play2),
inProgress(1),numbytes(0),num(0),currentPlayer(nullptr),waitingPlayer(nullptr),endTurn(0), gameOver(0), totalTurn(0){
    initGame();
}

Game::Game(const Game&) : myServer(nullptr),player1(nullptr),player2(nullptr),inProgress(1),numbytes(0),
num(0),currentPlayer(nullptr),waitingPlayer(nullptr),endTurn(0),gameOver(0),totalTurn(0){}

Game& Game::operator=(const Game&){
    return *this;
}

Game::~Game(){
    delete player1;
    delete player2;
}

void Game::initGame(){
    string msg;
    player1->drawFirstCards();
    player1->endTurn();

    player2->drawFirstCards();
    player1->setTurn();
}

int Game::isRunning(){
    return inProgress;
}

void Game::sendStringToPlayer(Player* playerX, string msg){
    if (send(playerX->getSocket(),const_cast<char*>(msg.c_str()),MAXSEND-1,0) == -1) {
        perror("recv");
        exit(1);
    }
}

void Game::receiveFromPlayer(Player* playerX){
    if ((numbytes=recv(playerX->getSocket(),msgPlayer,MAXSEND-1,0)) == -1){
        perror("recv");
        exit(1);
    }
    msgPlayer[numbytes] = '\0';
}

string Game::convertHandToString(Player* playerX){
    string stringHand = "";

    stringHand += "\x1B[31m\033[1m------- Votre main --------\033[0m\x1B[0m\n";
    for(unsigned i=0;i<playerX->getHand()->size();++i){
        stringHand += to_string(i) + " : " + (*(playerX->getHand()))[i].parseCard();
    }

    return stringHand;
}

void Game::yourTurn(){
    string turn = "1";
    sendStringToPlayer(currentPlayer,turn);
    currentPlayer->drawCard();
    currentPlayer->addEnergy();
    currentPlayer->restoreEnergy();
}

void Game::waitOpponentTurn(){
    string turn = "0";
    sendStringToPlayer(waitingPlayer, turn);

}

string Game::convertBoardToString(Player* playerX, Player* playerY){
    string board;
    board = "~~~~~~~~~~~~~~~           Tableau           ~~~~~~~~~~~~~~~~\n";
    board += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    board += "\t" + playerX->getUsername() + " : " + to_string(playerX->getHP()) + " HP , "
    + to_string(playerX->getCurrentEnergy()) + " Energie \n\n";
    for(unsigned i=0;i<playerX->getBoard()->size();++i){
        board += playerX->getCardInBoard(i).parseCard();
    }
    board += "###########################################################\n";
    for(unsigned j=0;j<playerY->getBoard()->size();++j){
        board += playerY->getCardInBoard(j).parseCard();
    }
    board += "\n\t" + playerY->getUsername() + " : " + to_string(playerY->getHP()) + " HP , "
    + to_string(playerY->getCurrentEnergy()) + " Energie \n";
    board += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    return board;
}

string Game::giveTargets(Player* playerX){
    string targets;
    for(unsigned i=0;i<playerX->getBoard()->size();++i){
        targets += playerX->getCardInBoard(i).guiParseCard() + "_";
    }
    return targets;
}

void Game::startTurn(){
    restoreAtkToMinions();
    yourTurn();
    waitOpponentTurn();
    receiveFromPlayer(waitingPlayer);	// ->Besoin de ça pour que ça boucle correctement chez WP
    receiveFromPlayer(currentPlayer);	// ->Pour voir si le client est tjr co
    num = numbytes;
    endTurn = 0;
}

int Game::isNotEmptyMsg(){
    return (strcmp(msgPlayer,""));
}

void Game::askOneCard(){
    string currentHand;
    currentHand = convertHandToString(currentPlayer);
    size_t handSize = currentPlayer->getHandSize();
    sendStringToPlayer(currentPlayer, to_string(handSize));
    receiveFromPlayer(currentPlayer);		//Recois ok
}

void Game::trySummon(){
    int test = atoi(msgPlayer) - 1;
    Card chosenCard = (*currentPlayer->getHand())[test];
    if (canPlayCard(chosenCard)){
        summon(chosenCard);
        removeCardFromPlayerHand(test);
        sendStringToPlayer(currentPlayer,"Invoc OK");
    }
    else{
        sendStringToPlayer(currentPlayer,"Invocation non-accepté !!");
    }
}

void Game::tryUsingCard(){
    string currentHand = guiConvertHand(currentPlayer);
    sendStringToPlayer(currentPlayer, currentHand);
    receiveFromPlayer(currentPlayer);		//Recois l'input
    if (strcmp(msgPlayer,"mainMenu")){	// toujours pas de déconnexion
        //Traiter input.
        trySummon();
    }
}

int Game::askPlayCard(){
    return (!strcmp(msgPlayer,"1"));
}

int Game::askAttack(){
    return (!strcmp(msgPlayer,"2"));
}

int Game::askDisconnected(){
    return (!strcmp(msgPlayer,"Deconnection"));
}

void Game::playOneCard(){
    askOneCard();
    if (isNotEmptyMsg()){		// Pas de déconnexion
        tryUsingCard();
    }
}

void Game::finishTurn(){
    endTurn = 1;
    currentPlayer->endTurn();
    waitingPlayer->setTurn();
}

int Game::askChat(){
    return (!strcmp(msgPlayer,"3"));
}

int Game::askFinishTurn(){
    return (!strcmp(msgPlayer,"4"));
}

int Game::askSurrender(){
    return (!strcmp(msgPlayer,"5"));
}

void Game::tryAttack(){
    int canAttackThisTurn = currentPlayer->nbrCanAttack();
    sendStringToPlayer(currentPlayer, to_string(canAttackThisTurn));
    if (canAttackThisTurn > 0){
        string canAtk = ableToAttackInBoard();
        sendStringToPlayer(currentPlayer, canAtk);
        receiveFromPlayer(currentPlayer);	//son monstre
        if (strcmp(msgPlayer,"mainMenu")){
            int chosenMinion = atoi(msgPlayer) -1;  // Indice canAtk;
            findTarget(chosenMinion);
        }
        else{
            currentPlayer->sendStringToWaitSocket("turnNotOver");
            waitingPlayer->sendStringToWaitSocket("turnNotOver");
        }
    }
    else{
        currentPlayer->sendStringToWaitSocket("turnNotOver");
        waitingPlayer->sendStringToWaitSocket("turnNotOver");
    }
}

void Game::sendTargets(){
    sendStringToPlayer(currentPlayer, to_string(waitingPlayer->getBoard()->size()+1));
    receiveFromPlayer(currentPlayer);			// Ok
    string targets = giveTargets(waitingPlayer);
    sendStringToPlayer(currentPlayer, targets);
    receiveFromPlayer(currentPlayer);	// Recois l'input
}

void Game::findTarget(int chosenMinion){
    sendTargets();
    if (strcmp(msgPlayer,"mainMenu")){
        if (!strcmp(msgPlayer,"1")){
            attackPlayer(chosenMinion);
        }
        else{
            doAttack(chosenMinion);
            //Minion vs Minion
        }
    }
    else{
        currentPlayer->sendStringToWaitSocket("turnNotOver");
        waitingPlayer->sendStringToWaitSocket("turnNotOver");
    }
}

void Game::infoEndGame(){
    sendStringToPlayer(waitingPlayer, to_string(totalTurn));
    sendStringToPlayer(currentPlayer, to_string(totalTurn));
    receiveFromPlayer(waitingPlayer);
    receiveFromPlayer(currentPlayer);
}

void Game::sendInfoKill(int indiceBoard){
    string cardName = currentPlayer->getCardInBoard(indiceBoard).getName();
    string msg = cardName + " a porté le coup de grâce à " + waitingPlayer->getUsername() + "\n";
    msg += "Sa puissante attaque de " + to_string(currentPlayer->getCardInBoard(indiceBoard).getAttack())
    + " n'a fait qu'une bouchée de l'ennemi. \n";
    sendStringToPlayer(waitingPlayer,msg);
    sendStringToPlayer(currentPlayer,msg);
}

void Game::surrender(){
    gameOver = 1;
    endTurn = 1;
    //////////////////////////////////////
    currentPlayer->lose();
    //////////////////////////////////////
    waitingPlayer->win();
    string msg = "winBySurrender";
    sendStringToPlayer(waitingPlayer,msg);
    receiveFromPlayer(waitingPlayer);
    //////////////////////////////////////
    infoEndGame();
    msg = currentPlayer->getUsername() + " a abandonné !!\n";
    msg += waitingPlayer->getUsername() + " est le grand vainqueur !!\n";
    sendStringToPlayer(waitingPlayer, msg);
    sendStringToPlayer(currentPlayer, msg);

    //Abandonner ? Why would someone Surrender. This is Sparta.
}

void Game::checkPlayerIsDead(){
    if (!waitingPlayer->isDead()){
        gameOver = 1;
        endTurn = 1;
        currentPlayer->win();
        currentPlayer->sendStringToWaitSocket("win");

        waitingPlayer->lose();
        waitingPlayer->sendStringToWaitSocket("lose");
    }
    else{
        currentPlayer->sendStringToWaitSocket("turnNotFinished");
        waitingPlayer->sendStringToWaitSocket("turnNotFinished");
    }
}

void Game::activeCheatEnergy(){
    for(int i=0;i<9;++i){
        currentPlayer->addEnergy();
        waitingPlayer->addEnergy();
    }
}

void Game::attackPlayer(int chosenMinion){
    int indiceBoard = currentPlayer->getCanAtk(chosenMinion);
    currentPlayer->disableAtkCardInBoard(indiceBoard);
    int damage = currentPlayer->getCardInBoard(indiceBoard).getAttack();
    waitingPlayer->receiveDamage(damage);
    checkPlayerIsDead();
}

void Game::doAttack(int chosenMin){
    int indiceBoard = currentPlayer->getCanAtk(chosenMin);
    int indiceTarget = atoi(msgPlayer) -1;
    --indiceTarget;
    int damage = currentPlayer->getCardInBoard(indiceBoard).getAttack();
    int counterAtk = waitingPlayer->getCardInBoard(indiceTarget).getAttack();
    // Doing the attack;
    int minionDied;
    waitingPlayer->receiveDamageOnMinion(indiceTarget, damage);
    minionDied = currentPlayer->receiveDamageOnMinion(chosenMin, counterAtk);
    if (minionDied){
        updateCanAtk(indiceBoard);
    }
    else{
        currentPlayer->disableAtkCardInBoard(indiceBoard);
    }
    currentPlayer->sendStringToWaitSocket("turnNotFinished");
    waitingPlayer->sendStringToWaitSocket("turnNotFinished");
}

void Game::updateCanAtk(int indiceBoard){
    size_t canAtkSize;
    canAtkSize = currentPlayer->getCanAtkSize();
    for(size_t i=0;i<canAtkSize;++i){
        int current = currentPlayer->getCanAtk(int(i));
        if (current > indiceBoard){
            currentPlayer->updateCanAtkIndice(int(i));
        }
    }
}

void Game::restoreAtkToMinions(){
    currentPlayer->allMinionsCanAtk();
}

string Game::ableToAttackInBoard(){
    currentPlayer->clearBoardAtk();
    string atk;
    int j = 0;
    for(size_t i=0;i<currentPlayer->getBoardSize();++i){
        if (currentPlayer->getCardInBoard(i).isAbleToAttack()){
            atk += currentPlayer->getCardInBoard(i).guiParseCard() + "_";
            currentPlayer->addCanAtkMinion(i);
            ++j;
        }
    }
    return atk;
}

void Game::playerDisconnected(){
    currentPlayer->lose();
    waitingPlayer->win();
    string msg = "Win";
    sendStringToPlayer(waitingPlayer,msg);
    gameOver = 1;
    endTurn = 1;
}

int Game::canPlayCard(Card playedCard){
    if (currentPlayer->getCurrentEnergy() < playedCard.getEnergyCost()){
        return 0;
    }
    currentPlayer->useEnergy(playedCard.getEnergyCost());
    return 1;
}

void Game::removeCardFromPlayerHand(int indice){
    currentPlayer->getHand()->erase(currentPlayer->getHand()->begin() + indice);
}

void Game::summon(Card playedCard){
    currentPlayer->addBoard(playedCard);
}

void Game::turnNotFinished(){
    waitOpponentTurn();
}

void Game::sendStartTurnToPlayers(){
    string msgBoardOrHand;
    msgBoardOrHand = convertBoardToString(currentPlayer, waitingPlayer);
    sendStringToPlayer(waitingPlayer,msgBoardOrHand);
    msgBoardOrHand = convertBoardToString(waitingPlayer, currentPlayer);
    sendStringToPlayer(currentPlayer,msgBoardOrHand);
    msgBoardOrHand = "\n" + convertHandToString(currentPlayer);
    sendStringToPlayer(currentPlayer,msgBoardOrHand);
}

void Game::sendBoardToWaiting(){
    string msgBoard;
    msgBoard = convertBoardToString(currentPlayer, waitingPlayer);
    sendStringToPlayer(waitingPlayer,msgBoard);
}

void Game::sendBoardAndHand(Player* currentPlayer, Player* waitingPlayer){
    string msgBoardOrHand;
    msgBoardOrHand = convertBoardToString(waitingPlayer, currentPlayer);
    sendStringToPlayer(currentPlayer,msgBoardOrHand);
    receiveFromPlayer(currentPlayer);
    msgBoardOrHand = "\n" + convertHandToString(currentPlayer);
    sendStringToPlayer(currentPlayer,msgBoardOrHand);
}

void Game::sendBoards(){
        guiSendBoardAndHand(waitingPlayer,currentPlayer);
        guiSendBoardAndHand(currentPlayer, waitingPlayer);

        receiveFromPlayer(currentPlayer);   //En attente de jeu.
        if (!strcmp(msgPlayer,"OK") || !strcmp(msgPlayer,"ok") || !strcmp(msgPlayer,"mainMenu")){
            receiveFromPlayer(currentPlayer);
        }
}

void Game::startGame(){
    int turnNewStart;
    while (!gameOver){
        turnNewStart = 1;
        ++totalTurn;
        currentPlayer = player1->isMyTurn() ? player1 : player2;
        waitingPlayer = player1->isMyTurn() ? player2 : player1;
        startTurn();
        while (!endTurn){
            if (!turnNewStart){
                sendStringToPlayer(currentPlayer,"1");
                sendStringToPlayer(waitingPlayer,"0");
                receiveFromPlayer(currentPlayer);
                receiveFromPlayer(waitingPlayer);
            }
            turnNewStart = 0;
            sendBoards();
            if (askPlayCard()){
                playOneCard();
                currentPlayer->sendStringToWaitSocket("turnNotOver");
                waitingPlayer->sendStringToWaitSocket("turnNotOver");
            }
            else if (askAttack()){
                tryAttack();
            }
            else if (askChat()){
                currentPlayer->startChat();
                turnNotFinished();
            }
            else if (askFinishTurn()){
                finishTurn();
                currentPlayer->sendStringToWaitSocket("opponentTurn");
                waitingPlayer->sendStringToWaitSocket("endTurn");
            }
            else if (askSurrender()){
                surrenderGui();
            }
            else if (askDisconnected()){
                gameOver = 1;
                endTurn = 1;
                //////////////////////////////////////
                currentPlayer->lose();
                //////////////////////////////////////
                waitingPlayer->win();
                //////////////////////////////////////
                disconnected();
            }
        }
        if (!num){
            cout << "-------------- Deconnection -------------- " << endl;
            playerDisconnected();
        }
    }
    inProgress = 0;
    //ECRIRE SUR LE FICHIER RANKING POUR METTRE A JOUR MERCI YOUCEF POUR TA GENEROSITE
}

void Game::disconnected(){
    waitingPlayer->sendStringToWaitSocket("winRageQuit");
}

void Game::surrenderGui(){
    gameOver = 1;
    endTurn = 1;
    //////////////////////////////////////
    currentPlayer->lose();
    //////////////////////////////////////
    waitingPlayer->win();
    //////////////////////////////////////
    waitingPlayer->sendStringToWaitSocket("surrenderWin");
    currentPlayer->sendStringToWaitSocket("surrenderLose");
}

string Game::guiConvertBoard(Player* playerX, Player* playerY){
    string board;
    board += playerX->getUsername() + "_";
    board += to_string(playerX->getHP()) + "_";
    board += to_string(playerX->getCurrentEnergy()) + "---";
    board += to_string(playerX->getBoard()->size()) + "_";
    for(unsigned i=0;i<playerX->getBoard()->size();++i){
        board += playerX->getCardInBoard(i).guiParseCard() + "_";
    }
    board += "---";      // ";;;" va séparer les 2 joueurs.
    board += to_string(playerY->getBoard()->size()) + "_";
    for(unsigned j=0;j<playerY->getBoard()->size();++j){
        board += playerY->getCardInBoard(j).guiParseCard() + "_";
    }
    board += "---";
    board += playerY->getUsername() + "_";
    board += to_string(playerY->getHP()) + "_";
    board += to_string(playerY->getCurrentEnergy());
    return board;
}

void Game::guiSendBoardToWaiting(){
    string msgBoard;
    msgBoard = guiConvertBoard(currentPlayer, waitingPlayer);
    sendStringToPlayer(waitingPlayer,msgBoard);
}

void Game::guiSendBoardAndHand(Player* currentPlayer, Player* waitingPlayer){
    string msgBoardOrHand;
    msgBoardOrHand = guiConvertBoard(waitingPlayer, currentPlayer);
    sendStringToPlayer(currentPlayer,msgBoardOrHand);
    receiveFromPlayer(currentPlayer);
    msgBoardOrHand = guiConvertHand(currentPlayer);
    sendStringToPlayer(currentPlayer,msgBoardOrHand);
}

string Game::guiConvertHand(Player* playerX){
    string stringHand;
    for(unsigned i=0;i<playerX->getHand()->size();++i){
        stringHand += (*(playerX->getHand()))[i].guiParseCard();
        if (i+1 < playerX->getHand()->size()){
            stringHand += "---";
        }
    }
    return stringHand;
}
