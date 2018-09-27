#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;

#define BuffSize 1024

class Client
{
private:
bool CreateSock();

int sock;                                 //Client used by socket
//These structs are used to combine the Addresses for clients and servers
//Along with the ports and the AF_INET family which represents IPv4 communication sockets
struct sockaddr_in client;
struct sockaddr_in server;

int counter=0;      //Counter used for timeouts

socklen_t x= sizeof(struct sockaddr_in);
char buffer[1024]="";

public:
Client(char * _hostname,int clientip, int _port);
int GetReply(int);
int DoOperation(string ,int , int);
~Client();
};
#endif // CLIENT_H
