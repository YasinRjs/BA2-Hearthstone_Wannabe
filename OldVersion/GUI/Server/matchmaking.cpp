#include "matchmaking.h"

Matchmaking::Matchmaking() : userInMatchmaking(vector<User*>()),userGameSockets(vector<int>()),userDecks(vector<GameDeck>()),
userChatManagers(vector<ChatManager*>()),userGameFd(vector<int>()),gameInProgress(),numberGames(0),myServer(nullptr)
{}

Matchmaking::Matchmaking(Server* server): userInMatchmaking(vector<User*>()),userGameSockets(vector<int>()),userDecks(vector<GameDeck>()),
userChatManagers(vector<ChatManager*>()),userGameFd(vector<int>()),gameInProgress(),numberGames(0), myServer(server){}

Matchmaking::~Matchmaking(){
    for (size_t i=0; i < gameInProgress.size(); ++i){
        delete gameInProgress[i];
    }
}

Matchmaking::Matchmaking(const Matchmaking&) : userInMatchmaking(vector<User*>()),userGameSockets(vector<int>()),userDecks(vector<GameDeck>()),
userChatManagers(vector<ChatManager*>()),userGameFd(vector<int>()),gameInProgress(),numberGames(0), myServer(nullptr){}

Matchmaking& Matchmaking::operator=(const Matchmaking&){
    return *this;
}

void Matchmaking::addUserInMatchmaking(User* user, int game_fd, GameDeck deck, ChatManager* cm, int gameFd){
    userInMatchmaking.push_back(user);
    userGameSockets.push_back(game_fd);
    userDecks.push_back(deck);
    userChatManagers.push_back(cm);
    userGameFd.push_back(gameFd);
    size_t indice = numberGames;
    if (userInMatchmaking.size() == 1){
        int flag = 0;
        while (!flag){
            if (gameInProgress.size() == indice+1){
                while (gameInProgress[indice]->isRunning()){
                }
                flag = 1;
            }
        }
    }
    if (userInMatchmaking.size() == 2){
        // Critical
        User* user1 = userInMatchmaking[0];
        userInMatchmaking.erase(userInMatchmaking.begin());
        User* user2 = userInMatchmaking[0];
        userInMatchmaking.erase(userInMatchmaking.begin());
        int sockfd1 = userGameSockets[0];
        userGameSockets.erase(userGameSockets.begin());
        int sockfd2 = userGameSockets[0];
        userGameSockets.erase(userGameSockets.begin());
        GameDeck deck1 = userDecks[0];
        userDecks.erase(userDecks.begin());
        GameDeck deck2 = userDecks[0];
        userDecks.erase(userDecks.begin());
        ChatManager* cm1 = userChatManagers[0];
        userChatManagers.erase(userChatManagers.begin());
        ChatManager* cm2 = userChatManagers[0];
        userChatManagers.erase(userChatManagers.begin());
        int gameFd1 = userGameFd[0];
        userGameFd.erase(userGameFd.begin());
        int gameFd2 = userGameFd[0];
        userGameFd.erase(userGameFd.begin());

        ++numberGames;
        createGame(user1, sockfd1, deck1, cm1, user2, sockfd2, deck2, cm2, gameFd1, gameFd2);
        // End critical
    }
}

void Matchmaking::createGame(User* user1, int sockfd1, GameDeck deck1, ChatManager* cm1, User* user2, int sockfd2, GameDeck deck2, ChatManager* cm2,
    int gameFd1, int gameFd2){

    if (send(sockfd1, const_cast<char*>(user2->getProfil().c_str()), MAXDATASIZE-1, 0) == -1) {
            perror("send");
            exit(1);
    }
    if (send(sockfd2, const_cast<char*>(user1->getProfil().c_str()), MAXDATASIZE-1, 0) == -1) {
            perror("send");
            exit(1);
    }

    Player* player1 = new Player(user1,deck1,sockfd1,cm1,gameFd1);
    Player* player2 = new Player(user2,deck2,sockfd2,cm2,gameFd2);
    Game* currentGame = new Game(myServer,player1,player2);
    gameInProgress.push_back(currentGame);
    gameInProgress[gameInProgress.size()-1]->startGame();

    // création 2 players
    // Création de gameManager
}
