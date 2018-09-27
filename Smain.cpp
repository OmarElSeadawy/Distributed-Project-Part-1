#include<iostream>
#include"Server.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string>
#include <string.h>
#include <netdb.h>
#include<unistd.h>
using namespace std;

int main(int argc, char **argv)
{
	//Translation from terminal functions
	char*point;
	int port =  strtol(argv[1],&point,10);
	int ipaddrserver = inet_addr(argv[2]);

	Server s1("Not Working",ntohl(ipaddrserver),port);
	s1.serverRequest();
	return 0;
}
