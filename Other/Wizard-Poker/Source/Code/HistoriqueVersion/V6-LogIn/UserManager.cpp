using namespace std;

#define MAXDATASIZE 200

class Server;

class UserManager{
	struct sockaddr_in my_addr;
	int new_fd,sockfd;
	pthread_t currentThread;
	Database* myDatabase;
	int numbytes;
	char msgClient[MAXDATASIZE];
public:
	UserManager(){};
	UserManager(ClientSocket*,int,Database*);
	~UserManager(){};

	void start();
	friend void* newConnection(void* arg);

	void receiveFromClient();
	void sendOKToClient();
	void sendNOToClient();
	void printNewConnection();
	void printEndConnection();
	void printBrutalDisconnect();
	void signIn();
	void signUp();
	void treatUser();
	void mainMenu();
//~~~~~~ Database
	int getUserID(string);
	int verifPasswordInDatabase(int,char*);
	int hasUserInDatabase(string);
	void addUserInDatabase(string,string);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};

void* newConnection(void* arg){
	UserManager* managerPtr = (UserManager*)arg;
	managerPtr->printNewConnection();
	managerPtr->treatUser();
	managerPtr->printEndConnection();
	pthread_exit(NULL);
}

UserManager::UserManager(ClientSocket* userSocket,int serverFd,Database* database)
	: my_addr(userSocket->getAddr()),new_fd(userSocket->getFd())
	,sockfd(serverFd),myDatabase(database){};

void UserManager::start(){
	pthread_create(&currentThread,NULL,newConnection,(void*)this);
}

void UserManager::treatUser(){
	receiveFromClient();
	//S'il veut se connecter
	if (!strcmp(msgClient,"2")){
		signIn();
	}
	//S'il veut s'inscrire
	else if (!strcmp(msgClient,"1")) {
		signUp();
		signIn();
	}
	else if (!strcmp(msgClient,"")){
		printBrutalDisconnect();
	}
}

void UserManager::receiveFromClient(){
	if ((numbytes=recv(new_fd,msgClient,MAXDATASIZE-1,0)) == -1){
		perror("recv");
	}
	msgClient[numbytes] = '\0';
}

//TODO Mettre parametre
void UserManager::sendOKToClient(){
	if ((send(new_fd,"OK",MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
}

void UserManager::sendNOToClient(){
	if ((send(new_fd,"NO",MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
}

void UserManager::printNewConnection(){
	cout << "Connection from : " << inet_ntoa(my_addr.sin_addr) << endl;
}

void UserManager::printEndConnection(){
	cout << "--> End of connection with : " << inet_ntoa(my_addr.sin_addr) << endl;
}

void UserManager::printBrutalDisconnect(){
	cout << "Brutal disconnect from : " << inet_ntoa(my_addr.sin_addr) << endl;
}

void UserManager::signIn(){
	int flag = 1;
	int id;
	while (flag){
		receiveFromClient();
		if (hasUserInDatabase(msgClient)){
			id = getUserID(msgClient);
			sendOKToClient();
			receiveFromClient();
			if (verifPasswordInDatabase(id,msgClient)){
				sendOKToClient();
				flag = 0;
				mainMenu();
			}
			else{
				sendNOToClient();
			}
		}
		else if (!strcmp(msgClient,"")){
			printBrutalDisconnect();
			flag = 0;
		}
		else{
			sendNOToClient();
		}
	}
}

void UserManager::signUp(){
	//TODO inscription
	int flag = 1;
	while (flag){
		receiveFromClient();
		if (!hasUserInDatabase(msgClient)){
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

int UserManager::getUserID(string username){
	return myDatabase->getID(username);
}

int UserManager::verifPasswordInDatabase(int id,char* pwd){
	return myDatabase->isCorrectPassword(id,pwd);
}

int UserManager::hasUserInDatabase(string username){
	return myDatabase->hasUserNamed(username);
}

void UserManager::addUserInDatabase(string username,string pwd){
	myDatabase->addUser(username,pwd);
}

void UserManager::mainMenu(){
	strcpy(msgClient,"mainMenu");
	while (!strcmp(msgClient,"mainMenu")){
		receiveFromClient();
		if (!strcmp(msgClient,"1")){
			//duel()
		}
		else if (!strcmp(msgClient,"2")){
			//collection()
		}
		else if (!strcmp(msgClient,"3")){
			//chat()
		}
		else if (!strcmp(msgClient,"4")){
			//classement
		}
		else if (!strcmp(msgClient,"5")){
			//quitter()
		}
		else if (!strcmp(msgClient,"")){
			printBrutalDisconnect();
		}
		else{
			strcpy(msgClient,"mainMenu");
		}
		cout << "Votre réponse : " << msgClient << endl;
	}
}