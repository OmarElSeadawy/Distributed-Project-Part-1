#include "Client.h"
#include <iostream>
#include <string>
using namespace std;


int main()
{
  string ip ="10.30.45.75";
  string serverip="10.7.57.229";
  int clientip=0x0A28234B;
  int serveripx=0x0A0739E5;

  Client cli("Henna",8080);
  cli.DoOperation("hello world",serveripx,8080);

  return 0;
}
