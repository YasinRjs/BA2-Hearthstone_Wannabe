#include "Server.hpp"

Server::Server() : my_addr(sockaddr_in()),allUsers(vector<User*>()),
	userConnected(vector<string>()),userChatSockets(vector<int>()) {

	CardDatabase* myCardDatabase = new CardDatabase();
	Database* myDatabase = new Database(myCardDatabase);
	createAllUsers(myDatabase);
	Ranking* myRanking = new Ranking(allUsers);
	Matchmaking* myMatchmaking = new Matchmaking(this);
	initServer();
	UserManager* userManager;
	cout << "Server est en marche..." << endl;
	while(1){
		userManager = new UserManager(acceptConnection(),myDatabase,myCardDatabase,myRanking,myMatchmaking,this);
		userManager->start();
	}

	delete myCardDatabase;
	delete myDatabase;
	delete myRanking;
	delete myMatchmaking;

}

Server::~Server(){
	for (size_t i = 0; i < allUsers.size(); ++i){
		delete allUsers[i];
	}
}


void Server::initServer(){
	initServerfd();
	initMyaddr();
	startBind();
	startListen();
	initSigaction();
}

void Server::createAllUsers(Database* database){
//	vector<User> userList = vector<User>();
	for(int i=0;i<database->getNbrUsers();++i){
		string username = database->getUsername(i);
		int victory = database->getVictory(i);
		int defeat = database->getDefeat(i);
		User* user = new User(to_string(i),username,victory,defeat);
		allUsers.push_back(user);
	}
	//allUsers = userList;
}


User* Server::getUserPtr(string username){
	int found = 0;
	size_t i = 0;
	User* userPtr;
	while (!found && i < allUsers.size()){
		if (allUsers[i]->getUsername() == username){
			found = 1;
			userPtr = allUsers[i];
		}
		++i;
	}
	return userPtr;
}

void Server::addUserInAllUsers(User* user){
	allUsers.push_back(user);
}

vector<User*> Server::getAllUsers(){
	return allUsers;
}

ClientSocket* Server::acceptConnection(){
	int new_fd, rcvMsgChat_fd, sendMsgChat_fd;
	struct sockaddr_in addr;
	socklen_t sin_size = sizeof(struct sockaddr_in);
	if ((new_fd = accept(serverfd,reinterpret_cast<struct sockaddr *>(&addr),&sin_size)) == -1){
		perror("accept");
		cout <<"sockfd"<<endl;
		exit(1);
	}
	if ((rcvMsgChat_fd = accept(serverfd,reinterpret_cast<struct sockaddr *>(&addr),&sin_size)) == -1){
		perror("accept");
		cout<<"rcvMsgChat_fd"<<endl;
		exit(1);
	}
	
	if ((sendMsgChat_fd = accept(serverfd,reinterpret_cast<struct sockaddr *>(&addr),&sin_size)) == -1){
		perror("accept");
		cout<<"sendMsgChat_fd"<<endl;
		exit(1);
	}


	return new ClientSocket(addr,new_fd, rcvMsgChat_fd, sendMsgChat_fd);
}

void Server::initServerfd(){
	if ((serverfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(1);
	}
	if (setsockopt(serverfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1){
		perror("setsockopt");
		exit(1);
	}
}

void Server::initMyaddr(){
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero),'\0',8);
}

void Server::startBind(){
	if (bind(serverfd, reinterpret_cast<struct sockaddr *>(&my_addr), sizeof(struct sockaddr)) == -1){
		perror("bind");
		exit(1);
	}
}

void Server::startListen(){
	if (listen(serverfd,BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
}

void Server::initSigaction(){
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD,&sa,nullptr) == -1) {
		perror("sigaction");
		exit(1);
	}  
}
//------------------------------------------------

vector<string> Server::getUserConnected(){
	return userConnected; 
}

string Server::getUser(int index){
	return userConnected[index];
}

int Server::getUserChatFd(int index){
	return userChatSockets[index];
}


void Server::addConnected(string username, int chat_fd){
	userConnected.push_back(username);
	userChatSockets.push_back(chat_fd);
}


void Server::printConnected(){
	cout << "Joueurs connectés: ";
	for (unsigned i = 0; i < userConnected.size(); ++i){
		cout << userConnected[i]+" ";
	}
	cout << endl;
}

void Server::removeDisconnected(int chat_fd){
	bool found = false;
	unsigned i = 0;
	while (!found && i<userChatSockets.size()){
		if (userChatSockets[i] == chat_fd){
			found = true;
			userChatSockets.erase(userChatSockets.begin()+i);		
		}
		++i;
	}
	if (found){
		userConnected.erase(userConnected.begin()+i-1);
	}
}


bool Server::isUserConnected(string username){
	bool found = false;
	unsigned i = 0;
	while (!found && i<userConnected.size()){
		if (userConnected[i] == username){
			found = true;
		}
    	++i;	
	}
	return found;
	
}




