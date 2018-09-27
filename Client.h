#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;

#defin BuffSize 1024

class Client
{
private:
bool CreateSock();

int sock;
struct sockaddr_in client;
struct sockaddr_in server;
int counter=0;
socklen_t x= sizeof(struct sockaddr_in);
char buffer[1024]="";

//extern "C" {
//char * inet_ntoa(struct in_addr);}

public:
Client(char * _hostname,int clientip, int _port);
int GetReply(int);
int DoOperation(string ,int , int);
~Client();
};
#endif // CLIENT_H
