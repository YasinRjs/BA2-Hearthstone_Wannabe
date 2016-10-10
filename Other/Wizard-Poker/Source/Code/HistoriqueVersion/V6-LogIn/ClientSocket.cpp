using namespace std;

class ClientSocket{
	struct sockaddr_in my_addr;
	int new_fd;
public:
	ClientSocket(){};
	ClientSocket(struct sockaddr_in,int);
	~ClientSocket(){};

	struct sockaddr_in getAddr();
	int getFd();
};

ClientSocket::ClientSocket(struct sockaddr_in addr,int fd) 
	: my_addr(addr),new_fd(fd){}

struct sockaddr_in ClientSocket::getAddr(){
	return my_addr;
}

int ClientSocket::getFd(){
	return new_fd;
}