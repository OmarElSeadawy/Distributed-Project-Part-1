
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
		server.sin_addr.s_addr= htonl(0x0A0739E5);
		server.sin_port=htons(_listen_port);
		if(!CreateSocket())
			cerr<<"socket failed\n";
		else
		cout<<"socket created\n";

		if(bind(sock,(sockaddr *) &server, sizeof(server)) <0)
			{
				cerr<<"bind failed\n";
				return;
			}
		else 
			cout<<"bind ok\n";

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
		socklen_t x= sizeof(struct sockaddr_in);
		int amount=recvfrom(sock,buffer,BuffSize,0, (sockaddr *) &client, (&x));
		return amount;
	}

int Server::serverReply()
	{
		if(sendto(sock,buffer,BuffSize,0,(sockaddr *) &client, (socklen_t) sizeof(&client))<0)
		{
			cerr<<"sending failed\n";
			return 0;
		}
		else
			return 1;
	}
Server::~Server()
	{
		//socket(sock);
	}

