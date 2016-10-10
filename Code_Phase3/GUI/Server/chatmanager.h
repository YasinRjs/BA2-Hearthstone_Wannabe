#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include "server.h"
#define MAXDATASIZE 500

using namespace std;

class Server;

class ChatManager{
    struct sockaddr_in my_addr;
    int sendChat_fd, recvChat_fd;
    char msgClient[MAXDATASIZE];
    Server* myServer;
    string username;
    ssize_t numbytes;
public:
    ChatManager();
    ChatManager(ClientSocket*, Server*);
    ChatManager(const ChatManager&);
    ChatManager& operator=(const ChatManager&);
    ~ChatManager();

    void addUsername(string);
    struct sockaddr_in getMyAddr();
    int getSendChatFd();
    int getRecvChatFd();
    void receiveFromClient();
    void receiveConfirmation(int);
    void sendMsgToClient(char*);
    void sendOKToClient();
    void sendNOToClient();
    int searchRecipientIndex(string);
    void startChat();
    string askClientForRecipient();
    void askClientForMsg(string);
    void sendMsgToRecipient(int);

    string getUsername();

    void loop();
    void sendConnected();

};

#endif // CHATMANAGER_H
