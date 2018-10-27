#ifndef CLIENT_H
#define CLIENT_H

enum MessageType={Request,Reply};

class Client
{
private:
	UDPClientSocket * udpSocket;
	char * hostname;
	int recv_port;
	int send_port;



	//void CommunicationModule();
	/*
		*sends the marshaled message created by the stub
		*recieves a reply from server and unmarshal it
	*/
	//Message * doOperation(int operationID);
	/*
		client side function uses time out
	parameters
		*remote reference IP address + a port number
		*operation ID
		*arguments array of bytes
	issues a send function - sends a request
	issues a recieve to get the reply uses a time out if there were no reply
	options for timeout
		* return with indication the doOperation has failed
		*
	request_messag would be of this structure

		Message Type
		requestID //should be unique for the client
		remoteRefenece
		operationID
		arquments

	*/


public:
	Client(char * _hostname, int _port);
	Message * execute(Message * _message);
	~Client();
};
#include "Client.cpp"
#endif // CLIENT_H
