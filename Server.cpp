
#include"Server.h"
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>


Server::Server(char * _listen_hostname,int serverip, int _listen_port)
	{
		//Initialize Server and Client with Zeroes
		memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

		server.sin_family=AF_INET;
		server.sin_addr.s_addr= htonl(serverip);
		server.sin_port=htons(_listen_port);
		if(!CreateSocket())
			cerr<<"socket failed\n";
		else
		cout<<"socket created\n";


		//Bind function which binds the socket with the address of the server
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
		//Similar to Client
		if((sock=socket(AF_INET,SOCK_DGRAM,0))<0)
			return 0;
		else
			return 1;
	}

int Server::serverRequest()
	{
		socklen_t x= sizeof(struct sockaddr_in);  //Needed for Recvfrom function
		int amount=0;
		struct timeval tv;
  	tv.tv_sec = 90;        // 90 Secs Timeout
  	tv.tv_usec = 0;
		client.sin_family=AF_INET;

		//All functions in the loop are almost equivalent to the client's side
		while(true)
			{
				setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));
				amount=recvfrom(sock,buffer,BuffSize,MSG_WAITALL, (sockaddr *) &client, (&x));
				if(amount==-1)
					{
						cout <<"Timeout\n";
						break;
					}
				else
					cout << "Size of message: " << amount << " Message: " << buffer << endl;
				if((amount==1)&&(buffer[0]=='q'))
					break;
				string replymsg(buffer);
				serverReply(replymsg);
				memset(buffer,NULL,BuffSize);

			}
		return amount;
	}
int Server::serverReply(string replymsg)
	{
		//Sending back the msg that was received from the client
		if(sendto(sock,replymsg.c_str(),replymsg.length(),MSG_CONFIRM,(sockaddr *) &client, sizeof(client))==-1)
		{
			cerr<<"Reply failed\n";
			return 0;
		}
		else
		{
			cout << "Reply succeeded\n";
			return 1;
		}
	}
Server::~Server()
	{
		close(sock);
	}
