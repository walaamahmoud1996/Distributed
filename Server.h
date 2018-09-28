#ifndef SERVER_H
#define SERVER_H
enum MessageType { Request, Reply};

class Server
{
private:

	MessageType message_type;
	UDPServerSocket * udpServerSocket;
	Message * getRequest();
	Message * doOperation();
	void sendReply (Message * _message);
	public:
	Server(char * _listen_hostname, int _listen_port);
	void serveRequest();
	~Server();
};
#include "Server.cpp"
#endif // SERVER_H