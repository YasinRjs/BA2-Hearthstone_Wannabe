#include "Player.hpp"
#include "ChatManager.hpp"

Player::Player() : myUser(nullptr),myDeck(GameDeck()),myHand(vector<Card>()),userChatManager(nullptr),
myBoard(vector<Card>()),canAtk(vector<int>()),hp(0),energy(0),currentEnergy(0),sockt(0),myTurn(0){}

Player::Player(User* user,GameDeck deck, int sockfd, ChatManager* cm)
 : myUser(user),myDeck(deck),myHand(vector<Card>()),userChatManager(cm),
 myBoard(vector<Card>()),canAtk(vector<int>()),hp(20),energy(0),currentEnergy(0),sockt(sockfd),myTurn(0){
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
	if (myHand.size() < 6){
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

void Player::showPlayerCards(){
	cout << "--- Création d'un nouveau Player ---" << endl;
	cout << "--- " << myUser->getUsername() << " ---" << endl;
	int cards = myDeck.getNbrCard();
	for(int i=0;i<cards;++i){
		(myDeck.getDeck())[i].showCard();
	}
}

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

void Player::receiveDamage(int damage){
	hp -= damage;
}

int Player::getCanAtkIndice(int indice){
	return canAtk[indice];
}

void Player::disableAtkCardInBoard(int indice){
	myBoard[indice].disableAttack();
}

void Player::receiveDamageOnMinion(int targetIndice, int damage){
	Card* cardPtr;
	cardPtr = &myBoard[targetIndice];

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
	}
}

int Player::isDead(){
	return hp>0;
}