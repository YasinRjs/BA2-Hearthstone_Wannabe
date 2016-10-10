#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MAXDATASIZE 200
#define PORT 5555
#define BACKLOG 10

#include "Database.cpp"
#include "User.cpp"

using namespace std;

void sigchld_handler(int s){
	while(wait(NULL) > 0);
}

class Server{
	int sockfd,new_fd;
	int numbytes;
	char msgClient[MAXDATASIZE];
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes;
	Database myDatabase;
public:
	void initServer();
	void acceptConnection();
	void receiveFromClient();
	void sendOKToClient();
	void sendNOToClient();
	void printNewConnection(){
		cout << "Connection from : " << inet_ntoa(their_addr.sin_addr) << endl;
	}
	void printEndConnection(){
		cout << "--> End of connection with : " << inet_ntoa(their_addr.sin_addr) << endl;
	}
	void signIn();
	void signUp();
	void treatUser();

//~~~~~~~~~ Database
	void addUserInDatabase(string username,string password);

	Server() : yes(1),myDatabase(Database()){
		initServer();
		while(1){
			acceptConnection();
			printNewConnection();
			if (!fork()){
				treatUser();

				printEndConnection();
				exit(0);
			}
		}
	}

};
//TODO Mettre parametre
void Server::sendOKToClient(){
	if ((send(new_fd,"OK",MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
}
void Server::sendNOToClient(){
	if ((send(new_fd,"NO",MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
}

void Server::receiveFromClient(){
	if ((numbytes=recv(new_fd,msgClient,MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
	msgClient[numbytes] = '\0';
}

void Server::acceptConnection(){
	sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(sockfd,(struct sockaddr *)&their_addr,&sin_size)) == -1){
		perror("accept");
		exit(1);
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

void Server::treatUser(){
	close(sockfd);
	receiveFromClient();
	//S'il veut se connecter
	if (!strcmp(msgClient,"2")){
		signIn();
	}
	//S'il veut s'inscrire
	else if (!strcmp(msgClient,"1")) {
		signUp();
		signIn();
		myDatabase.onlyForHackers();
	}
	printEndConnection();
	exit(0);
}

void Server::signIn(){
	int flag = 1;
	while (flag){
		receiveFromClient();
		if (myDatabase.hasUserNamed(msgClient)){
			int id = myDatabase.getID(msgClient);
			sendOKToClient();
			receiveFromClient();
			if (myDatabase.isCorrectPassword(id,msgClient)){
				sendOKToClient();
				flag = 0;
				//Menu principale  GOTO					----
			}
			else{
				sendNOToClient();
			}
		}
		else{
			sendNOToClient();
		}
	}
}

void Server::signUp(){
	//TODO inscription
	int flag = 1;
	while (flag){
		receiveFromClient();
		if (!myDatabase.hasUserNamed(msgClient)){
			sendOKToClient();
			string username = msgClient;
			receiveFromClient();
			string pwd = msgClient;
			addUserInDatabase(username,pwd);
			flag = 0;
		}
		else{
			sendNOToClient();
		}
	}
}

void Server::addUserInDatabase(string username,string password){
	myDatabase.addUser(username,password);
}


int main(int argc,char *argv[]){
	Server server = Server();
	return 0;
}