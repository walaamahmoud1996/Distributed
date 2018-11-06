#include <iostream>
#include <stddef.h>

#include "Server.h"

//#include "UDPClientSocket.h"
using namespace std;

int main(){

	string str = "127.0.0.1";
	char* ip =strcpy((char*)malloc(str.length()+1),str.c_str());
	Server x(ip, 1234);
	x.serveRequest();


	return 0;
}
