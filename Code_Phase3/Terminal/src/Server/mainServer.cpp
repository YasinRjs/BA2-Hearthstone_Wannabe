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


#include "ChatManager.hpp"
#include "Database.hpp"
#include "User.hpp"
#include "ClientSocket.hpp"
#include "UserManager.hpp"
#include "Server.hpp"

//------------------------------------------------
//------------------------------------------------
int main(){
	Server server = Server();
	return 0;
}
//------------------------------------------------
//------------------------------------------------