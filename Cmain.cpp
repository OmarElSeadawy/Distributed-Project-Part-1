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

  int ipaddrserver = inet_addr(argv[2]);
  int ipaddrclient = inet_addr(argv[3]);

  char*point;
  int port = strtol(argv[1],&point,10);
  int count;
  Client cli("Not Working",ntohl(ipaddrclient),port);
  string msg;

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
