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

  int port = 1350;
  int clientip=0x0A28234B;
  int serveripx=0x0A283555;


  //struct hostent *hp = gethostbyname(argv[1]);

  /*unsigned int i=0;
  while ( hp -> h_addr_list[i] != NULL) {
   printf( "%s ", inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
   i++;
 }*/
  Client cli("x",port);
  string msg;

  do
  {
    cin >> msg;
    cli.DoOperation(msg,serveripx,port);
  }while(msg != "q");



  //cli.GetReply();
  return 0;
}
