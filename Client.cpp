#include "Client.h"
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string>
#include <string.h>
#include <netdb.h>
#include<unistd.h>
using namespace std;

#define BuffSize 1024

Client::Client(char * _hostname, int _port)
{

  //struct hostent* Hostinfo = gethostbyname(_hostname);

  //char * IPAdd = inet_ntoa(Hostinfo->h_addr_list[0]);

  memset(&server, 0, sizeof(server));
  memset(&client, 0, sizeof(client));

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = htonl(0x0A28234B);
  client.sin_port = htons(_port);

  //cout << htonl(0x0A28234B) << " " << htons(_port) << endl;
  if(!CreateSock())
    cerr << ("socket failed");
  else
    cout << "Socket Created\n";


/*
  if(bind(sock,(sockaddr *) &client, sizeof(client)) < 0)
    {
      cerr << ("bind failed\n");
      return;
    }
  else
    cout << "bind Created\n";
*/
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

    //cout << client.sin_addr.s_addr << " " << client.sin_port << endl;

  if(sendto(sock , msg.c_str(), msg.length(), MSG_CONFIRM, (sockaddr *) &server , sizeof(struct sockaddr_in)) == -1 )
    {
      cerr << "Sending Failed\n";
      return;
    }
  cout << "Sending Succeded\n";
  cout <<"started get reply" << endl;

  int amount = recvfrom(sock, buffer,BuffSize,MSG_WAITALL, (sockaddr *) &server, &x);
  cout << "Size of Reply: " << amount << " Reply from server: " << buffer << endl;

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
  cout <<"started get reply" << endl;
  int amount = recvfrom(sock, buffer,BuffSize,0, (sockaddr *) &server, (&x));
  cout << "Size of Reply: " << amount << " Reply from server: " << buffer << endl;
}
*/
