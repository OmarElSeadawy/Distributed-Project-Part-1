
#include"Server.h"
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


Server::Server(char * _listen_hostname, int _listen_port)
	{

		memset(&server, 0, sizeof(server));
  	memset(&client, 0, sizeof(client)); 

		server.sin_family=AF_INET;
		server.sin_addr.s_addr= htonl(0x0a283555);
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
		int amount=0;

		client.sin_family=AF_INET;
			amount=recvfrom(sock,buffer,BuffSize,MSG_WAITALL, (sockaddr *) &client, (&x));
			cout << "Size of message: " << amount << " Message: " << buffer << endl;
			messagelen=amount;
			string replymsg(buffer);
			serverReply(replymsg);
			memset(buffer,NULL,BuffSize);
		return amount;
	}

int Server::serverReply(string reply)
	{
		//int amount=1;
		//cout << client.sin_port <<" "<< client.sin_addr.s_addr << endl;
		//cout << reply << " " << reply.length()<< endl;
		if(sendto(sock,reply.c_str(),reply.length(),MSG_CONFIRM,(sockaddr *) &client, sizeof(client))==-1)
		{
			cerr<<"Reply failed\n";
			return 0;
		}
		else
		{
			//cout << amount << endl;
			cout << "Reply succeeded\n";
			return 1;
		}
	}
Server::~Server()
	{
		//closesocket(sock);
	}
