#ifndef ClientSocket_HPP_
#define ClientSocket_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class ClientSocket{
	struct sockaddr_in my_addr;
	int new_fd, recvChat_fd, sendChat_fd;
public:
	ClientSocket();
	ClientSocket(struct sockaddr_in,int,int, int);
	~ClientSocket();

	struct sockaddr_in getAddr();
	int getFd();
	int getSendChatFd();
	int getRecvChatFd();
};

#endif /* ClientSocket_HPP_ */
