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

#define BuffSize 50

Client::Client(char * _hostname, int _port)
{

  memset(&server, 0, sizeof(server));
  memset(&client, 0, sizeof(client));

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = htonl(0x0A28234B);
  client.sin_port = htons(_port);

  if(!CreateSock())
    cerr << ("socket failed");
  else
    cout << "Socket Created\n";

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
    GetReply(msg.length());
}
bool Client::CreateSock()
{
  if(( sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    return 0;
  else
    return 1;
}

void Client::GetReply(int l)
{
  struct timeval tv;
  tv.tv_sec = 10;        // 30 Secs Timeout
  tv.tv_usec = 0;        // Not init'ing this can cause strange errors
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));

  cout <<"Waiting for Reply" << endl;
  int amount = recvfrom(sock, buffer,BuffSize,MSG_WAITALL, (sockaddr *) &server, &x);
  if(amount == -1)
    cout << "TimeOut\n";
  else
  {
    if(l != amount)
      cout << "Message is Incomplete\n";
    cout << "Size of Reply: " << amount << " Reply from server: " << buffer << endl;
  }
}
