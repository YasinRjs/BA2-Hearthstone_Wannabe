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

using namespace std;

class Server{
	int sockfd;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes;
	Database myDatabase;
	int sockets[MAXDATASIZE];
	int nbrUser;
	int current;
public:
	Server();
	~Server(){};

	friend void* newConnection(void*);

	void initServer();
	void acceptConnection();
	void receiveFromClient(char*,int);
	void sendOKToClient(int);
	void sendNOToClient(int);
	void printNewConnection();
	void printEndConnection();
	void signIn(int);
	void signUp(int);
	void treatUser(int);
//~~~~~~~~~ Message to Database
	void addUserInDatabase(string username,string password);
//~~~~~~~~~
};

void* newConnection(void* arg){
	Server* serverPtr = (Server*)arg;
	int thisUser = serverPtr->current;
	serverPtr->treatUser(thisUser);
	serverPtr->printEndConnection();
	pthread_exit(NULL);
}

void sigchld_handler(int s){
	while(wait(NULL) > 0);
}

Server::Server() : yes(1),myDatabase(Database()),nbrUser(-1){
	for(int i=0;i<MAXDATASIZE;++i){
		sockets[i]=0;
	}
	initServer();
	while(1){
		pthread_t newUser;
		acceptConnection();
		current=nbrUser;
		++nbrUser;
		printNewConnection();
		pthread_create(&newUser,NULL,newConnection,(void*)this);
	}
}

void Server::initServer(){
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1){
		perror("setsockopt");
		exit(1);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero),'\0',8);
	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}
	if (listen(sockfd,BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD,&sa,NULL) == -1) {
		perror("sigaction");
		exit(1);
	}  
}

void Server::acceptConnection(){
	sin_size = sizeof(struct sockaddr_in);
	if ((sockets[nbrUser] = accept(sockfd,(struct sockaddr *)&their_addr,&sin_size)) == -1){
		perror("accept");
		exit(1);
	}
	for(int i=0;i<10;++i){
		cout << "socket : " << sockets[i] << endl;
	}
}

void Server::receiveFromClient(char *msgClient,int thisUser){
	int numbytes;
	if ((numbytes=recv(sockets[thisUser],msgClient,MAXDATASIZE-1,0)) == -1){
		perror("recv");
	}
	msgClient[numbytes] = '\0';
}

//TODO Mettre parametre
void Server::sendOKToClient(int thisUser){
	if ((send(sockets[thisUser],"OK",MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
}
void Server::sendNOToClient(int thisUser){
	if ((send(sockets[thisUser],"NO",MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
}

void Server::printNewConnection(){
	cout << "Connection from : " << inet_ntoa(their_addr.sin_addr) << endl;
}

void Server::printEndConnection(){
	cout << "--> End of connection with : " << inet_ntoa(their_addr.sin_addr) << endl;
}

void Server::signIn(int thisUser){
	char msgClient[MAXDATASIZE];
	int flag = 1;
	while (flag){
		receiveFromClient(msgClient,thisUser);
		if (myDatabase.hasUserNamed(msgClient)){
			int id = myDatabase.getID(msgClient);
			sendOKToClient(thisUser);
			receiveFromClient(msgClient,thisUser);
			if (myDatabase.isCorrectPassword(id,msgClient)){
				sendOKToClient(thisUser);
				flag = 0;
				//Menu principale  GOTO					----
			}
			else{
				sendNOToClient(thisUser);
			}
		}
		else{
			sendNOToClient(thisUser);
		}
	}
}

void Server::signUp(int thisUser){
	//TODO inscription
	char msgClient[MAXDATASIZE];
	int flag = 1;
	while (flag){
		receiveFromClient(msgClient,thisUser);
		if (!myDatabase.hasUserNamed(msgClient)){
			sendOKToClient(thisUser);
			string username = msgClient;
			receiveFromClient(msgClient,thisUser);
			string pwd = msgClient;
			addUserInDatabase(username,pwd);
			flag = 0;
		}
		else{
			sendNOToClient(thisUser);
		}
	}
}

void Server::treatUser(int thisUser){
	char msgClient[MAXDATASIZE];
	receiveFromClient(msgClient,thisUser);
	//S'il veut se connecter
	if (!strcmp(msgClient,"2")){
		signIn(thisUser);
	}
	//S'il veut s'inscrire
	else if (!strcmp(msgClient,"1")) {
		signUp(thisUser);
		signIn(thisUser);
		myDatabase.onlyForHackers();
	}
}

void Server::addUserInDatabase(string username,string password){
	myDatabase.addUser(username,password);
}

//#####################################################################
int main(int argc,char *argv[]){
	Server server = Server();
	return 0;
}
//#####################################################################