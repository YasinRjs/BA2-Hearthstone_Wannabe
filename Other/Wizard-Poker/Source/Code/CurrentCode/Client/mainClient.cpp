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

#include "Client.hpp"
//--------------------------------------------
//--------------------------------------------
int main(int argc, char* argv[]){
	Client x = Client(argc,argv[1]);
	return 0;
}
//--------------------------------------------
//--------------------------------------------