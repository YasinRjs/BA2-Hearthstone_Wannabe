#include "player.h"

Player::Player() : myUser(nullptr),myDeck(GameDeck()),myHand(vector<Card>()),userChatManager(nullptr),
myBoard(vector<Card>()),canAtk(vector<int>()),hp(0),energy(0),currentEnergy(0),sockt(0),myTurn(0){}

Player::Player(User* user,GameDeck deck, int sockfd, ChatManager* cm, int game_fd)
 : myUser(user),myDeck(deck),myHand(vector<Card>()),userChatManager(cm),
 myBoard(vector<Card>()),canAtk(vector<int>()),hp(20),energy(0),currentEnergy(0),sockt(sockfd),myTurn(0),waitingSocket(game_fd){
}

Player::Player(const Player&) : myUser(nullptr),myDeck(GameDeck()),myHand(vector<Card>()),userChatManager(nullptr),
myBoard(vector<Card>()),canAtk(vector<int>()),hp(0),energy(0),currentEnergy(0),sockt(0),myTurn(0){}

Player& Player::operator=(const Player&){
    return *this;
}

Player::~Player(){}

void Player::drawFirstCards(){
    int firstRoundDraw = 2;
    for(int i=0;i<firstRoundDraw;++i){
        drawCard();
    }
}

int Player::getSocket(){
    return sockt;
}

void Player::drawCard(){
    //Max 6 cartes dans la main
    if (myHand.size() < 5){
        myHand.push_back(myDeck.giveCard());
    }
}

vector<Card>* Player::getHand(){
    vector<Card>* newHand = &myHand;
    return newHand;
}

vector<Card>* Player::getBoard(){
    vector<Card>* newBoard = &myBoard;
    return newBoard;
}

Card Player::getCardInBoard(size_t indice){
    return myBoard[indice];
}

/*
void Player::showPlayerCards(){
    cout << "--- Création d'un nouveau Player ---" << endl;
    cout << "--- " << myUser->getUsername() << " ---" << endl;
    int cards = myDeck.getNbrCard();
    for(int i=0;i<cards;++i){
        (myDeck.getDeck())[i].showCard();
    }
}
*/

int Player::isMyTurn(){
    return myTurn;
}

void Player::setTurn(){
    myTurn = 1;
}

void Player::addEnergy(){
    if (energy < 10){
        ++energy;
    }
}

void Player::endTurn(){
    myTurn = 0;
}

void Player::startChat(){
    userChatManager->startChat();
}

int Player::getChatFd(){
    return userChatManager->getRecvChatFd();
}

void Player::printBrutalDisconnect(){
    cout << "~~> Deconnection brutale de : " << inet_ntoa(userChatManager->getMyAddr().sin_addr) << endl;
}

void Player::win(){
    myUser->incVictory();
}

void Player::lose(){
    myUser->incDefeat();
}

string Player::getUsername(){
    return myUser->getUsername();
}

int Player::getHP(){
    return hp;
}

int Player::getCurrentEnergy(){
    return currentEnergy;
}

size_t Player::getHandSize(){
    return myHand.size();
}

void Player::addBoard(Card card){
    myBoard.push_back(card);
}

void Player::restoreEnergy(){
    currentEnergy = energy;
}

void Player::useEnergy(int cost){
    currentEnergy -= cost;
}

size_t Player::getBoardSize(){
    return myBoard.size();
}

int Player::nbrCanAttack(){
    int canAtk = 0;
    for(size_t i=0;i<getBoardSize();++i){
        if (myBoard[i].isAbleToAttack()){
            ++canAtk;
        }
    }
    return canAtk;
}

void Player::clearBoardAtk(){
    canAtk.clear();
}

void Player::addCanAtkMinion(size_t indice){
    canAtk.push_back(static_cast<int>(indice));
}

void Player::allMinionsCanAtk(){
    for(unsigned i=0;i<myBoard.size();++i){
        myBoard[i].enableAttack();
    }
}

int Player::getCanAtk(int indice){
    return canAtk[indice];
}

size_t Player::getCanAtkSize(){
    return canAtk.size();
}

void Player::eraseCanAtk(int indice){
    canAtk.erase(canAtk.begin() + indice);
}

void Player::updateCanAtkIndice(int indice){
    canAtk[indice] = canAtk[indice] - 1;
}

void Player::receiveDamage(int damage){
    hp -= damage;
}

int Player::getCanAtkIndice(int indice){
    return canAtk[indice];
}

void Player::disableAtkCardInBoard(int indice){
    myBoard[indice].disableAttack();
}

int Player::receiveDamageOnMinion(int targetIndice, int damage){
    Card* cardPtr;
    cardPtr = &myBoard[targetIndice];
    int flag = 0;
    cardPtr->receiveDamage(damage);
    if (!cardPtr->isAlive()){
        for(unsigned i=0;i<myBoard.size();++i){
            if (&myBoard[i] == &myBoard[targetIndice]){
                for(unsigned j=0;j<canAtk.size();++j){
                    if (canAtk[j] == int(i)){
                        canAtk.erase(canAtk.begin()+j);
                    }
                }
            }
        }
        myBoard.erase(myBoard.begin()+targetIndice);
        flag = 1;
    }
    return flag;
}

int Player::isDead(){
    return hp>0;
}

void Player::setWaitingSocket(int sock){
    waitingSocket = sock;
}

void Player::sendStringToWaitSocket(string msg){
    if ((send(waitingSocket,msg.c_str(),MAXDATASIZE-1,0)) == -1) {
        perror("recv");
        exit(1);
    }    
}