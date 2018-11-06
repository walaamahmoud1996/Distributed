#include <iostream>
#include <stddef.h>

#include "Client.h"
#include "Message.h"

//#include "UDPClientSocket.h"
using namespace std;

int main(){

	string str = "127.0.0.1";
	char* ip =strcpy((char*)malloc(str.length()+1),str.c_str());

	Client x(ip, 1234);

	//operation 1: view Image
	vector<string> args;
	args.push_back("hi.jpg");
	args.push_back("ahmed");

	Message y(1, Request, args, args[0].size()+args[1].size(), 0);

	x.execute(y);

	return 0;
}
