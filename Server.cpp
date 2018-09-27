#include"Server.h"
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;

Server::Server(char * _listen_hostname, int _listen_port)
	{
		server.sin_family=AF_INET;
		server.sin_addr.s_addr= _listen_hostname;
		server.sin_port=htons(_listen_port);
		if(!CreateSocket(sock))
			cerr<<"socket failed\n";
		else
			cout<<"socket created\n";

		if(bind(sock,(SOCKADDR *) &server, sizeof(server)) <0)
			{
				cerr<<"bind failed\n";
				return 1;
			}

	}

bool Server::CreateSocket()
	{
		if((sock=socket(AF_INET,SOCK_DGRAM,0))<0)
			return 0;
		else
			return 1;
	}
int Server::serverRequest()
	{
		return (recvfrom(s,buffer,BuffSize,0, client));
	}
int Server::serverReply()
	{
		if(sendto(s,buffer,BuffSize,0,(SOCKADDR *) &client, sizeof(client))<0)
		{
			cerr<<"sending failed\n";
			return 0;
		}
		else
		{
			cout << "Sending Succeeded\n";
			return 1;
		}
	}
Server::~Server()
	{
		close(sock);
	}
