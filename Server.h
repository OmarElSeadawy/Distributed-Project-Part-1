#ifndef SERVER_H
#define SERVER_H
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
using namespace std;
#define  BuffSize 1024

class Server{
private:
	bool CreateSocket();
	int sock;
	int messagelen=0;
	char buffer[BuffSize]="";

	struct sockaddr_in server;
	struct sockaddr_in client;
public:

	Server(char * _listen_hostname,int serverip,int _listen_port);
	int serverRequest();
	int serverReply(string);
	~Server();
};

#endif //SERVER_H
