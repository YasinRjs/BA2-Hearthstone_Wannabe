#include "ChatManager.hpp"

ChatManager::ChatManager() : my_addr(sockaddr_in()),sendChat_fd(0),recvChat_fd(0),myServer(nullptr),
username(""),numbytes(0)
{}

ChatManager::ChatManager(ClientSocket* userSocket, Server* server): my_addr(userSocket->getAddr()), sendChat_fd(userSocket->getSendChatFd()), recvChat_fd(userSocket->getRecvChatFd()), myServer(server),
	username(""),numbytes(0){}

ChatManager::ChatManager(const ChatManager&) : my_addr(sockaddr_in()),sendChat_fd(0),recvChat_fd(0),myServer(nullptr),
username(""),numbytes(0){}

ChatManager& ChatManager::operator=(const ChatManager&){
	return *this;
}

ChatManager::~ChatManager(){}

void ChatManager::addUsername(string name){
	username = name;
}

struct sockaddr_in ChatManager::getMyAddr(){
	return my_addr;
}


int ChatManager::getSendChatFd(){
	return sendChat_fd;
}

int ChatManager::getRecvChatFd(){
	return recvChat_fd;
}

void ChatManager::receiveFromClient(){
	if ((numbytes=recv(sendChat_fd,msgClient,MAXDATASIZE-1,0)) == -1){
		perror("recv");
		exit(1);
	}
	msgClient[numbytes] = '\0';	
}

void ChatManager::receiveConfirmation(int sockfd){
	char ok[2];
	if ((numbytes=recv(sockfd,ok,2,0)) == -1){
		perror("recv");
		exit(1);
	}	
}

void ChatManager::sendMsgToClient(char* msg){
	if (send(sendChat_fd, msg, MAXDATASIZE-1, 0) == -1) {
		perror("send");
		exit(1);		
	}	
}

void ChatManager::sendOKToClient(){
	if ((send(sendChat_fd,"OK",MAXDATASIZE-1,0)) == -1){
		perror("send");
		exit(1);
	}
}

void ChatManager::sendNOToClient(){
	if ((send(sendChat_fd,"NO",MAXDATASIZE-1,0)) == -1){
		perror("send");
		exit(1);
	}
}

int ChatManager::searchRecipientIndex(string recipient){
	vector<string> allUsersConnected = myServer->getUserConnected();
	int recipientIndex = -1;
	unsigned i = 0;
	while (recipientIndex == -1 && i < allUsersConnected.size()){
		if (recipient == allUsersConnected[i]){
			recipientIndex = i;
		}
		++i;
	}

	return recipientIndex;
}




void ChatManager::startChat(){
	string recipient = askClientForRecipient();
	if (recipient != ""){
		if (myServer->isUserConnected(recipient)){
			sendOKToClient();
			askClientForMsg(recipient);
			if (myServer->isUserConnected(recipient)){
				sendOKToClient();
				int recipientIndex = searchRecipientIndex(recipient);
				sendMsgToRecipient(recipientIndex);
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

string ChatManager::askClientForRecipient(){
	vector<string> allUsersConnected = myServer->getUserConnected();
	allUsersConnected.push_back("&");
	int userIndex;
	for (unsigned i = 0; i < allUsersConnected.size(); ++i){
		if (username != allUsersConnected[i]){
			// Conversion de string en char*
			char* username =const_cast<char*>(allUsersConnected[i].c_str());
			sendMsgToClient(username);
			receiveConfirmation(sendChat_fd);
		}
		else{
			userIndex = i;
		}
	}
	receiveFromClient();
	string recipientUsername;
	int recipientIndex = atoi(msgClient) - 1;
	if (recipientIndex == -1){
		recipientUsername = "";
	}
	else{
		if (recipientIndex >= userIndex){
			recipientIndex += 1;
		}
		recipientUsername = allUsersConnected[recipientIndex];
	}
	return recipientUsername;
}

void ChatManager::askClientForMsg(string recipient){
	char* recipientUsername = const_cast<char*>(recipient.c_str());
	sendMsgToClient(recipientUsername);
	receiveFromClient();
}

void ChatManager::sendMsgToRecipient(int recipientIndex){
	int recipient_fd = myServer->getUserChatFd(recipientIndex);
	if (send(recipient_fd, const_cast<char*>(username.c_str()), MAXDATASIZE-1, 0) == -1) {
		perror("send");
		exit(1);		
	}
	receiveConfirmation(recipient_fd);
	if (send(recipient_fd, msgClient, MAXDATASIZE-1, 0) == -1) {
		perror("send");
		exit(1);
	}
	receiveConfirmation(recipient_fd);

}

string ChatManager::getUsername(){
	return username;
}