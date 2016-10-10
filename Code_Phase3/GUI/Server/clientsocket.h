#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class ClientSocket{
    struct sockaddr_in my_addr;
    int new_fd, recvChat_fd, sendChat_fd, game_fd;
public:
    ClientSocket();
    ClientSocket(struct sockaddr_in,int,int, int, int);
    ~ClientSocket();

    struct sockaddr_in getAddr();
    int getFd();
    int getSendChatFd();
    int getRecvChatFd();
    int getGameFd();
};

#endif // CLIENTSOCKET_H
