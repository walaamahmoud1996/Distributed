#include "Client.h"

Client::Client(char * _hostname, int _port)
{


	if(udpSocket.initializeClient(_hostname,_port)){
		cout <<"Client in intialized\n";
		udpSocket.enable();
	}
	else
		cout<<"Failed To intialize a Client\n";



}

/////// send a message and returns a reply //////////
Message* Client::execute(Message _message){

	int maxBytes = _message.getMessageSize();
	string str = (_message.marshal());
	cout << str << endl;
	char* buffer = strcpy((char*)malloc(str.length()+1),str.c_str());
	cout << buffer << endl;
	udpSocket.writeToSocketAndWait(buffer,maxBytes,3,0);

}
Client::~Client(){}
