#ifndef CLIENT_H
#define CLIENT_H
class Client
{
private:
	UDPClientSocket * udpSocket;
	char * hostname;
	int recv_port;
	int send_port;
public:
	Client(char * _hostname, int _port);
	Message * execute(Message * _message);
	~Client();
};
#include "Client.cpp"
#endif // CLIENT_H