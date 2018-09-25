#include "Client.h"
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string>
using namespace std;

#define BuffSize 1024

Client::Client(char * _hostname, int _port)
{

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = htonl(0x0A28234B);
  client.sin_port = htons(_port);

  if(!CreateSock())
    cerr << ("socket failed");
  else
    cout << "Socket Created\n";

  if(bind(sock,(sockaddr *) &client, sizeof(client)) < 0)
    {
      cerr << ("bind failed\n");
      return;
    }
  else
    cout << "bind Created\n";

}
Client::~Client()
{
  //close(sock);
}

void Client::DoOperation(string msg, int serverip, int serverport)
{
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(serverip);
    server.sin_port = htons(serverport);
    
    cout << msg << " " << msg.length() << endl;
  if(sendto(sock , msg.c_str(), msg.length(), 0, (sockaddr *) &server , sizeof(struct sockaddr_in)) == -1 )
    {
      cerr << "Sending Failed\n";
      return;
    }
  cout << "Sending Succeded\n";
}
bool Client::CreateSock()
{
  if(( sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    return 0;
  else
    return 1;
}
/*
void Client::GetReply()
{
  recvfrom(sock, buffer,BuffSize,0, (sockaddr *) &server , (socklen_t*) sizeof(&server));
}*/
