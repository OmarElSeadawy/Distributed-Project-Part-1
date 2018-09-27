#ifndef CLIENT_H
#define CLIENT_H
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;

class Client
{
private:
bool CreateSock();

int sock;
struct sockaddr_in client;
struct sockaddr_in server;
socklen_t x= sizeof(struct sockaddr_in);
char buffer[1024]="";

//extern "C" {
//char * inet_ntoa(struct in_addr);}

public:
Client(char * _hostname, int _port);
void GetReply(int);
void DoOperation(string ,int , int);
~Client();
};
#endif // CLIENT_H



//Message * execute(Message * _message);
//UDPClientSocket * udpSocket;
//Message * doOperation();
