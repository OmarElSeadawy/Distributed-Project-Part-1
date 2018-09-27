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

  int ipaddr = inet_addr(argv[2]);

  char*point;
  int port = strtol(argv[1],&point,10);
  int clientip=0x0A28234B;
  int serveripx=ntohl(ipaddr);
  int count;
  Client cli("x",port);
  string msg;

  do
  {
    getline(cin,msg);
    count=cli.DoOperation(msg,serveripx,port);
    if(msg == "q")
      break;
    else if(count>2)
      break;  
    //cli.GetReply();
  }while(true);


  return 0;
}
