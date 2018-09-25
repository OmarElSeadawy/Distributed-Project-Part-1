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
char * buffer;

public:
Client(char * _hostname, int _port);
void GetReply();
void DoOperation(string ,int , int);
~Client();
};
#endif // CLIENT_H



//Message * execute(Message * _message);
//UDPClientSocket * udpSocket;
//Message * doOperation();
