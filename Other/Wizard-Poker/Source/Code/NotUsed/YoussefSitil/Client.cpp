#include "Client.hpp"

Client::Client(int argSize,char* ip) : inputPlayer("0"),msgServer("0") {
	// --------------- NEW -----------------------//
	//createRandomDecks();
	for(int i = 0; i < numberOfDeck; ++i)
	{
		deckList[i] = Deck(myCollection);
	}
	// ---------------- NEW ------------------------//

	verifArgs(argSize);
	init(ip);
	welcomeMsg();
	askConnection();
	sendInputToServer();
	traceDiese();
	if (!strcmp(inputPlayer,"3")){
		leaveMsg();
		//TODO disconnect();
	}
	else if (strcmp(inputPlayer,"1")){
		signIn();
	}
	else{
		signUp();
	}
}

void Client::verifArgs(int argSize){
	if (argSize < 2){
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

	if ((chat_fd=socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(my_addr.sin_zero),'\0',8);
	if (connect(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
	  perror("connect");
	  cout <<"sockfd"<<endl;
	  exit(1);
	}
	if (connect(chat_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1){
	  perror("connect");
	  cout << "chatfd" << endl;
	  exit(1);
	}

	// -------------- NEW -------------------//
		
	// Traiter les message de miguel pour remplir cardsList et dim
	// reste encore à rajouter ici	
	myCollection = Collection();
	
	// -------------- NEW -------------------//
}

void Client::welcomeMsg(){
	cout << "Bienvenue sur Wizard-Poker !\n- 1 : S'inscrire\n- 2 : Se connecter\n- 3 : Quitter" << endl;
}

void Client::traceLigne(){
	cout << "---------------------------------------" << endl;
}

void Client::traceDiese(){
	cout << "########################################" << endl;
}

void Client::leaveMsg(){
	cout << "Ce jeu est trop difficile pour vous !" << endl;
}

void Client::askConnection(){
	//Réponse du joueur à "se connecter"
	while (strcmp(inputPlayer,"1") && strcmp(inputPlayer,"2") && strcmp(inputPlayer,"3")){
		cout << "Votre réponse (1,2,3) : ";
		cin >> inputPlayer;
	}
}

void Client::sendInputToServer(){
	if (send(sockfd,inputPlayer,MAXDATASIZE-1,0) == -1) {
		perror("recv");
		exit(1);
	}
}

void Client::receiveFromServer(){
	if ((numbytes=recv(sockfd,msgServer,MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
	msgServer[numbytes] = '\0';
}

void Client::signIn(){
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
				sendInputToServer();
				receiveFromServer();
				if (!strcmp(msgServer,"OK")){
					cout << "Connection réussie, Have fun !" << endl;
					traceDiese();
					mainMenu();
				}
				else{
					cout << "Cet utilisateur est déjà connecté."<<endl;
					traceLigne();
					strcpy(inputPlayer,"");

				}
			}
			else{
				cout << "Mot de passe refusé" << endl;
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

void Client::signUp(){
	strcpy(inputPlayer,"");
	cout << "~~ Vous allez tenter de vous inscrire ~~" << endl;
	while (!(strcmp(inputPlayer,""))){
		cout << "Nom d'utilisateur : ";
		cin >> inputPlayer;
		sendInputToServer();
		receiveFromServer();
		if (!strcmp(msgServer,"OK")){
			cout << "Mot de passe : ";
			cin >> inputPlayer;
			sendInputToServer();
			cout << "~~~~ Compte créé avec succès ~~~~" << endl;
			cout << "~~~~ Veuillez vous connecter ~~~~" << endl;
			signIn();
		}
		else{
			cout << "Nom d'utilisateur déjà utilisé !" << endl;
			traceLigne();
			strcpy(inputPlayer,"");
		}
	}
}

void Client::mainMenu(){
	int flag = 1;
	cout << "~~~~ Main Menu ~~~~" << endl;
	cout << "- 1 : Recherche d'un adversaire" << endl;
	cout << "- 2 : Collection" << endl;
	cout << "- 3 : Discuter" << endl;
	cout << "- 4 : Classement" << endl;
	cout << "- 5 : Quitter le jeu" << endl;

	while (flag){
		cout << "Votre Réponse ( 1,2,3,4 ou 5 ) : ";
		cin >> inputPlayer;
		if (isCorrectInput(inputPlayer)){
			flag = 0;
		}
	}
	sendInputToServer();
	if (!strcmp(inputPlayer,"1")){
		cout << "~~ Recherche d'adversaire ~~" << endl;
		//findOpponent();
	}
	else if (!strcmp(inputPlayer,"2")){
		cout << "~~ Ouverture de la collection ~~" << endl;
		//openCollection();
	}
	else if (!strcmp(inputPlayer,"3")){
		cout << "~~ Ouverture du chat ~~" << endl;
		startChat();
	}
	else if (!strcmp(inputPlayer,"4")){
		cout << "~~ Classement ~~" << endl;
		//printClassement();
	}
	else if (!strcmp(inputPlayer,"5")){
		cout << "~~ Quitter le jeu ~~" << endl;
		leaveMsg();
		//disconnect()  --- Enlever de la liste des personnes en ligne ---
	}
}

int Client::isCorrectInput(char* input){
	return (!strcmp(input,"1") || !strcmp(input,"2") || !strcmp(input,"3") \
			|| !strcmp(input,"4") || !strcmp(input,"5"));
}

void* receiveChat(void* arg){
	Client* clientPtr = (Client*) arg;
	clientPtr->chatReception();
	delete clientPtr;
	pthread_exit(NULL);
}

void Client::start(){
	pthread_create(&chatThread,NULL,receiveChat,(void*) this);
}

void Client::chatReception(){
	while (1){
		if ((msgNumbytes=recv(sockfd,msgChat,MAXDATASIZE-1,0)) == -1){
			perror("recv chat");
			exit(1);
		}
		msgChat[msgNumbytes] = '\0';
		cout << msgChat << endl;
	}
}
//-----------------------------------------------------------------------------
void Client::startChat(){ 
	int userIndex = 1;
	while(strcmp(msgServer,"&")){
		if ((numbytes=recv(chat_fd,msgServer,MAXDATASIZE-1,0)) == -1){
			perror("recv");
			exit(1);
		}
		if (send(chat_fd,"ok",MAXDATASIZE-1,0) == -1) {  	
			perror("recv");
			exit(1);		
		}

	        msgServer[numbytes] = '\0';
	        if (strcmp(msgServer,"&")){
	        	cout<<userIndex<<"."<<msgServer<<" ";
	        } 
	        userIndex += 1;
	}
	cout << endl;

}









