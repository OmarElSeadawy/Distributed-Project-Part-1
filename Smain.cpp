#include<iostream>
#include"Server.h"

using namespace std;

int main()
{
	Server s1("M",1360);
	//while(!s1.serverRequest())
	//{}
	s1.serverRequest();
	//s1.serverReply();
	return 0;
}
