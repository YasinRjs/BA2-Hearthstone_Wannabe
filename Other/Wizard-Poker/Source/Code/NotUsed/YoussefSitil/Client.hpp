#ifndef Client_H_
#define Client_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

// -------------New------------------ //
#include "Deck.h"
#include "Collection.h"
#include "Database.h"
#define numberOfDeck 5
// -------------New------------------ //

#define MAXDATASIZE 200
#define PORT 5555


using namespace std;

class Client{
	// -------------New------------------ //
	Collection myCollection;
	Deck deckList[5];
	// -------------New------------------ //

	char inputPlayer[MAXDATASIZE];
	char msgServer[MAXDATASIZE];
	int sockfd,numbytes;
	struct sockaddr_in my_addr;
	struct hostent *he;
//----------------------------------------
	int chat_fd, msgNumbytes;
	pthread_t chatThread;
	char msgChat[MAXDATASIZE];
public:
	Client(){};
	Client(int argSize,char* ip);
	~Client(){};

	void verifArgs(int argSize);
	void init(char* ip);
	void welcomeMsg();
	void traceLigne();
	void traceDiese();
	void leaveMsg();
	void askConnection();
	void sendInputToServer();
	void receiveFromServer();
	void signIn();
	void signUp();
	void mainMenu();
	int isCorrectInput(char*);
	

//----------------------------------------
	void start();
	friend void* receiveChat(void* arg);
	void chatReception();
	void startChat();
};

#endif /* Client_H_ */
