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
	args.push_back("indexZ.jpg");
	args.push_back("ahmed");

	Message y(1445, Request, args, 22);
	//cout << y.getOperation() << endl;
	Message printed = x.execute(y);
	vector<string> aho = printed.getMessage();

	cout << aho[0]<<endl;
	ofstream fout("output.jpg", ios::binary);
	fout << aho[1];
	fout.close();
	return 0;
}
