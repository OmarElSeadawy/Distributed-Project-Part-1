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

Client::Client(char * _hostname,int clientip, int _port)
{

  //Initialize the server and client structs with zeroes
  memset(&server, 0, sizeof(server));
  memset(&client, 0, sizeof(client));

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = htonl(clientip);
  client.sin_port = htons(_port);

  if(!CreateSock())
    cerr << ("socket failed");
  else
    cout << "Socket Created\n";

}
Client::~Client()
{
  close(sock);
}

int Client::DoOperation(string msg, int serverip, int serverport)
{
    //Assign the server struct with IP and Port specified by user
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(serverip);
    server.sin_port = htons(serverport);


    //Sendto function from systemcalls which sends the message to the serverReply
    //It takes the socket, message and its length along with server Addresses
    // MSG_CONFIRM flag allows the sendto make sure the msg was sent correctly
  if(sendto(sock , msg.c_str(), msg.length(), MSG_CONFIRM, (sockaddr *) &server , sizeof(struct sockaddr_in)) == -1 )
    {
      cerr << "Sending Failed\n";
      return 0;
    }
    cout << "Sending Succeeded\n";
    return GetReply(msg.length());
}

bool Client::CreateSock()
{
  //Functions that creates socket, SOCK_DGRAM is used in UDP communication
  //According to several resources, binding the client was not needed explicitly
  //As the sendto function automatically binds the structs of the client address
  // and the program worked fine without using bind

  if(( sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    return 0;
  else
    return 1;
}

int Client::GetReply(int l)
{

  struct timeval tv;
  tv.tv_sec = 10;          //10 seconds till timeout if no reply was recieved from server
  tv.tv_usec = 0;          //Had to be initialized to avoid problems
  //This function manipulates socket options at API level, it lets recvfrom function to timeout after the specified times
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));

  cout <<"Waiting for Reply" << endl;
  memset(buffer,NULL,BuffSize);
  //Recvfrom function which is blocking recieve and MSG_WAITALL flag waits for entire msg to deliver
  int amount = recvfrom(sock, buffer,BuffSize,MSG_WAITALL, (sockaddr *) &server, &x);
  if(amount == -1){
    cout << "TimeOut\n";
    counter++;
  }
  else
  {
    if(l != amount)
      cout << "Message is Incomplete\n";
    cout << "Size of Reply: " << amount << " Reply from server: " << buffer << endl;

    counter=0;
  }
  return counter;
}
