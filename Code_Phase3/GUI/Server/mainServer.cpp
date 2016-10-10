#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <vector>

#define MAXDATASIZE 500
#define PORT 5555
#define BACKLOG 10


#include "chatmanager.h"
#include "database.h"
#include "user.h"
#include "clientsocket.h"
#include "usermanager.h"
#include "server.h"

//------------------------------------------------
//------------------------------------------------
int main(){
	srand(time(nullptr));
	Server server = Server();
	return 0;
}
//------------------------------------------------
//------------------------------------------------