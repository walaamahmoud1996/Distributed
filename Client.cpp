#include "Client.h"



Client::Client(char * _hostname, int _port)
{


	if(udpSocket->intializeClient(_hostname,_port)){
		cout <<"Client in intialized\n";
		UDPClientSocket.enable();
	}
	else
		cout<<"Failed To intialize a Client\n";



}

/////// send a message and returns a reply //////////
Message* Client::execute(Message * _message){

	int maxBytes = _message.getMessageSize();
	char* buffer = (char*)_message.getMessage();
	udpSocket->writeToSocketAndWait(buffer,maxBytes,3,0);

}
Client::~Client();
