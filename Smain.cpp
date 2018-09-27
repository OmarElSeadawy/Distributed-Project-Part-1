#include<iostream>
#include"Server.h"

using namespace std;

int main(int argc, char **argv)
{
	Server s1("Not Working",strtol(argv[1],&point,10));
	s1.serverRequest();
	return 0;
}
