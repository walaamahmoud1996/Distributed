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
	Message * y = new Message(0, Request, "a7eh", 4, 0);

	x.execute(y);

	return 0;
}
