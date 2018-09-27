#ifndef SERVER_H
#define SERVER_H
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;
#define BuffSize 1024
class Server{
private:
	int sockfd,newsockfd,portno,clilen n;
	bool CreateSocket(int&);
	int sock;
	struct sockaddr_in server;
	char * buffer;
	struct sockaddr_in client;
public:
	
	Server(char * _listen_hostname, int _listen_port);
	int serverRequest(int s);
	int serverReply();
	~Server();
}


#endif //SERVER_H
