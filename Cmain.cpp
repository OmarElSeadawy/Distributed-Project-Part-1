#include "Client.h"
#include <iostream>
#include <string>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<unistd.h>
using namespace std;

int main(int argc, char **argv)
{

  // Inet_addr function is used to translates IPv4 address format
  // into binary data in network byte order
  // These 2 lines translte Client and Server IP provided in terminal
  int ipaddrserver = inet_addr(argv[2]);
  int ipaddrclient = inet_addr(argv[3]);

  char*point;
  int port = strtol(argv[1],&point,10);
  int count;
  //Here Constructor of the Client is called and it creates the socket used lateron
  Client cli("Not Working",ntohl(ipaddrclient),port);
  string msg;

  //The do-while loop is to keep providing input from user until
  // The user either enters 'q' or recvfrom function times out 3 times
  //DoOperation does all the sending and recieving and will be explained in Client.cpp
  do
  {
    getline(cin,msg);
    count=cli.DoOperation(msg,ntohl(ipaddrserver),port);
    if(msg == "q")
      break;
    else if(count>2)
      break;
  }while(true);


  return 0;
}
