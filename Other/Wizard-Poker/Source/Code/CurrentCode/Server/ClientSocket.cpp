#include "ClientSocket.hpp"

ClientSocket::ClientSocket() : my_addr(sockaddr_in()),new_fd(0),recvChat_fd(0),sendChat_fd(0)
{}

ClientSocket::ClientSocket(struct sockaddr_in addr,int fd, int recv_fd, int send_fd) 
	: my_addr(addr),new_fd(fd), recvChat_fd(recv_fd), sendChat_fd(send_fd)
	{}

ClientSocket::~ClientSocket(){}

struct sockaddr_in ClientSocket::getAddr(){
	return my_addr;
}

int ClientSocket::getFd(){
	return new_fd;
}

int ClientSocket::getSendChatFd(){
	return sendChat_fd;
}

int ClientSocket::getRecvChatFd(){
	return recvChat_fd;
}