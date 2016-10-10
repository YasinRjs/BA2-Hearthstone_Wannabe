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

#define MAXDATASIZE 200
#define PORT 5555

using namespace std;


class Client{
	char inputPlayer[MAXDATASIZE];
	char msgServer[MAXDATASIZE];
	int sockfd,numbytes;
	struct sockaddr_in my_addr;
	struct hostent *he;
public:
	void verifArgs(int argc);
	void init(char* ip);
	void welcomeMsg(){
		cout << "Bienvenue sur Wizard-Poker !\n- 1 : S'inscrire\n- 2 : Se connecter\n- 3 : Quitter" << endl;
	}
	void traceLigne(){
		cout << "---------------------------------------" << endl;
	}
	void traceChangementFenetre(){
		cout << "########################################" << endl;
	}
	void askConnection();
	void sendInputToServer();
	void receiveFromServer();
	
	Client(int argc,char* ip) : inputPlayer("0"),msgServer("0") {
		verifArgs(argc);
		init(ip);
		welcomeMsg();
		askConnection();
		sendInputToServer();
		traceLigne();
		if (!strcmp(inputPlayer,"3")){
			cout << "Ce jeu est trop difficile pour vous !" << endl;
			exit(0);
		}
		//Début de la connection ou inscription
		//Si inputPlayer différent de 1 donc se connecter
		if (strcmp(inputPlayer,"1")){
			strcpy(inputPlayer,"");
			//Demande username
			while (!(strcmp(inputPlayer,""))){
				cout << "Nom d'utilisateur : ";
				cin >> inputPlayer;
				sendInputToServer();
				receiveFromServer();
				//Mot de Passe
				if (!strcmp(msgServer,"OK")){
					cout <<"Mot de passe : ";
					cin >> inputPlayer;
					sendInputToServer();
					receiveFromServer();
					if (!strcmp(msgServer,"OK")){
						cout << "Connection réussie, Have fun !" << endl;
						traceChangementFenetre();
						exit(0);
					}
					else{
						cout <<"Mot de passe refusé" << endl;
						traceLigne();
						strcpy(inputPlayer,"");
					}
				}
				else{
					cout << "Nom d'utilisateur refusé" << endl;
					traceLigne();
					strcpy(inputPlayer,"");
				}
			}
		}
		else{
			//Inscription
		}
	}
};

void Client::receiveFromServer(){
	if ((numbytes=recv(sockfd,msgServer,MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
	msgServer[numbytes] = '\0';
}

void Client::sendInputToServer(){
	if (send(sockfd,inputPlayer,MAXDATASIZE-1,0) == -1) {
		perror("recv");
		exit(1);
	}
}
void Client::askConnection(){
	//Réponse du joueur à "se connecter"
	while (strcmp(inputPlayer,"1") && strcmp(inputPlayer,"2") && strcmp(inputPlayer,"3")){
		cout << "Votre réponse (1,2,3) : ";
		cin >> inputPlayer;
	}
}

void Client::verifArgs(int argc){
	if (argc < 2){
		cout << "Manque adresse ip" << endl;
		exit(1);
	}
}
void Client::init(char* ip){
	if ((he = gethostbyname(ip)) == NULL){
		perror("gethostbyname");
		exit(1);
	}
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(my_addr.sin_zero),'\0',8);
	if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
	  perror("connect");
	  exit(1);
	}
}



int main(int argc, char* argv[]){
	Client x = Client(argc,argv[1]);
	return 0;
}



/*
void Client::askConnection(){
	//Réponse du joueur à "se connecter"
	while (strcmp(inputPlayer,"1") && strcmp(inputPlayer,"2")){
		cout << "Votre réponse (1 ou 2) : ";
		cin >> inputPlayer;
	if (strcmp(inputPlayer,"1")){
		cout << "Se connecter" << endl;
	}
	else{
		cout << "S'inscrire"<< endl;
	}
*/
