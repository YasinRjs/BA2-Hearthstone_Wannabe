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

void welcomeMsg(){
  cout << "Bienvenue sur Wizard-Poker !\n- 1 : S'inscrire\n- 2 : Se connecter" << endl;
}
void traceLigne(){
  cout << "---------------------------------------" << endl;
}
void askConnection(char* inputPlayer){
  //Réponse du joueur à "se connecter"
  while (strcmp(inputPlayer,"1") && strcmp(inputPlayer,"2")){
    cout << "Votre réponse (1 ou 2) : ";
    cin >> inputPlayer;
  }
/*  if (strcmp(inputPlayer,"1")){
    cout << "Se connecter" << endl;
  }
  else{
    cout << "S'inscrire"<< endl;
  }
*/
}

int main(int argc,char *argv[]) {
  char inputPlayer[MAXDATASIZE] = "0";
  char msgServer[MAXDATASIZE] = "0";
  int sockfd,numbytes;
  struct sockaddr_in my_addr;
  struct hostent *he;
//-----------------------------------------------Inititialisation 
  if (argc != 2){
    fprintf(stderr,"Il manque l'adresse ip\n");
    exit(1);
  }
  if ((he=gethostbyname(argv[1])) == NULL) {
    perror("gethostbyname");
    exit(1);
  }
  if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
    perror("socket");
    exit(1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(PORT);
  my_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(my_addr.sin_zero), '\0', 8);
  if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
    perror("connect");
    exit(1);
  }
//-----------------------------------------------Inititialisation 

  welcomeMsg();
  askConnection(inputPlayer);
  //Envoie de la réponse au serveur
  if (send(sockfd,inputPlayer,MAXDATASIZE-1,0) == -1) {
    perror("recv");
    exit(1);
  }
  traceLigne();
  //Début de la Connection
  if (strcmp(inputPlayer,"1")){
    strcpy(inputPlayer,"");
    //Connexion, d'abord Username
    while (!(strcmp(inputPlayer,""))){
      cout << "Nom d'utilisateur : ";
      cin >> inputPlayer;
      if (send(sockfd,inputPlayer,MAXDATASIZE-1,0) == -1) {
        perror("recv");
        exit(1);
      }
      if ((numbytes=recv(sockfd,msgServer,MAXDATASIZE-1,0)) == -1) {
        perror("recv");
        exit(1);
      }
        msgServer[numbytes] = '\0';
      //Mot de passe
      if (!strcmp(msgServer,"OK")){
        cout << "Mot de passe : ";
        cin >> inputPlayer;
        if (send(sockfd,inputPlayer,MAXDATASIZE-1,0) == -1) {
          perror("recv");
          exit(1);
        }
        if ((numbytes=recv(sockfd,msgServer,MAXDATASIZE-1,0)) == -1) {
          perror("recv");
          exit(1);
        }
        msgServer[numbytes] = '\0';
        if (!strcmp(msgServer,"OK")){
          traceLigne();
          cout << "Connection réussie, it's time to play the game !" << endl;
        }
        else{
          traceLigne();
          cout << "Mot de passe refusé" << endl;
        }
        exit(0);
      }
      else{
        traceLigne();
        cout << "Nom d'utilisateur refusé" << endl;
        exit(0);
      }
    }
    //TODO Menu principal
  }
  //-----
  //Début de l'inscription
  else{
  
  }
  
  
  return 0;
}



  
