#include "Client.h"



Client::Client(char * _hostname, int _port)
{
	

	if(udpSocket->intializeClient(_hostname,_port)){


	}
	else
		cout<<"Failed To intialize a Client\n";



}

/////// send a message and returns a reply //////////
Message *Client:: execute(Message * _message){

	int maxBytes = _message.getMessageSize();
	char* buffer = (char*)_message.getMessage();
	udpSocket->writeToSocketAndWait(buffer,maxBytes);



		



		
}
Client::~Client();
