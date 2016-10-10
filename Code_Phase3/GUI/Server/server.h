#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <pthread.h>
#include <vector>

#define MAXDATASIZE 500
#define PORT 5555
#define BACKLOG 10

#include "database.h"
#include "user.h"
#include "clientsocket.h"
#include "usermanager.h"

using namespace std;

class Server{
    int serverfd = 0;
    int serverChatfd = 0;
    struct sockaddr_in my_addr;
    int yes = 1;
    //-------------------
    vector<User*> allUsers;
    vector<string> userConnected;
    vector<int> userChatSockets;
public:
    Server();
    ~Server();

    ClientSocket* acceptConnection();
    void initServer();
    void initServerfd();
    void initMyaddr();
    void startBind();
    void startListen();
    void initSigaction();
//-------------------------------
    void createAllUsers(Database*);
    User* getUserPtr(string);
    void addUserInAllUsers(User*);
    vector<User*> getAllUsers();
//--------------------------------
    vector<string> getUserConnected();
    string getUser(int);
    int getUserChatFd(int);
    void addConnected(string, int);
    void printConnected();
    void removeDisconnected(int);
    bool isUserConnected(string);
    int getSocket();

};

#endif // SERVER_H
