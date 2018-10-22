#ifndef SERVER_H
#define SERVER_H


class Server
{
private:

	
	UDPServerSocket * udpServerSocket;
	Message * getRequest();//unmarshall
	void sendReply (Message * _message);//marshall
	


	public:
	Server(char * _listen_hostname, int _listen_port);
	
	void serveRequest();
	/*
		
		1- getRequest
		unmarshal and unserialize
		verify that the msg is of type request
		get the operation id
		call the do operation function
		sendReply 
		verify that it is of type reply
		marshal the msg 
		send it


	*/
	~Server();
};
#include "Server.cpp"
#endif // SERVER_H