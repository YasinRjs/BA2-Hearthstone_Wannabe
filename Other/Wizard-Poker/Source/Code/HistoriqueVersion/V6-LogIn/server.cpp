#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
//#include <signal.h>
#include <pthread.h>

#define MAXDATASIZE 200
#define PORT 5555
#define BACKLOG 10

#include "Database.cpp"
#include "User.cpp"
#include "ClientSocket.cpp"
#include "UserManager.cpp"

using namespace std;

void sigchld_handler(int s){
	while(wait(NULL) > 0);
}

class Server{
	int serverfd;
	struct sockaddr_in my_addr;
	struct sigaction sa;
	int yes;
	Database* myDatabase;
public:
	Server();
	~Server(){};

	ClientSocket* acceptConnection();
	void initServer();
	void initServerfd();
	void initMyaddr();
	void startBind();
	void startListen();
	void initSigaction();
};

Server::Server() : yes(1){
	Database* myDatabase = new Database();
	initServer();
	UserManager* userManager;
	while(1){
		userManager = new UserManager(acceptConnection(),serverfd,myDatabase);
		userManager->start();
	}
}

void Server::initServer(){
	initServerfd();
	initMyaddr();
	startBind();
	startListen();
	initSigaction();
}

ClientSocket* Server::acceptConnection(){
	int new_fd;
	struct sockaddr_in addr;
	socklen_t sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(serverfd,(struct sockaddr *)&addr,&sin_size)) == -1){
		perror("accept");
		exit(1);
	}
	return new ClientSocket(addr,new_fd);
}

void Server::initServerfd(){
	if ((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	if (setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1){
		perror("setsockopt");
		exit(1);
	}
}

void Server::initMyaddr(){
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero),'\0',8);
}

void Server::startBind(){
	if (bind(serverfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}
}

void Server::startListen(){
	if (listen(serverfd,BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
}

void Server::initSigaction(){
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD,&sa,NULL) == -1) {
		perror("sigaction");
		exit(1);
	}  
}

//#####################################################################
int main(int argc,char *argv[]){
	Server server = Server();
	return 0;
}
//#####################################################################