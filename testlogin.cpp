#include <iostream>
#include "DServer.h"
using namespace std;

int main(){
	char* ip = copyStr("127.0.0.1");
	DServer s(ip,3000);

	s.serveRequest();

	return 0;
}