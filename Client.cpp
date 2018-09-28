#include "Client.h"



Client::Client(char * _hostname, int _port)
{
	this->hostname = _hostname;
	this->send_port = _port;

	if(udpSocket->intializeClient(_hostname,_port)){


	}
	else
		cout<<"Failed To intialize a Client\n";



}

/////// send a message and returns a reply //////////
Message *Client:: execute(Message * _message){


		



		if( (n = sendto(s, message, strlen(message), 0,udpSocket->get,sizeof(struct sockaddr_in))) < 0) perror("Send 2 failed\n");

}
Client::~Client();
