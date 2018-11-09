#ifndef SERVER_H
#define SERVER_H
#include "UDPServerSocket.h"
#include "Message.h"
#include <string>
#include <cstring>
#include <thread>
#include <map>
#include <utility>
#include<algorithm>
#include "image.h"

class Server
{
private:

	map<pair<pair<string, int>, int>, vector<string>> Log;
	map<pair<pair<string, int>, int>, struct sockaddr_in> targetLog;
	int reqID;
	map<int,pair<string, int>> reqHist;
	UDPServerSocket udpServerSocket;
	bool matchPackets(string);
	Message  getRequest();//unmarshall
	void sendReply (Message _message);//marshall
	Message doOperation(Message requested);




	int getPacketNumber(string message, bool& end);

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
//#include "Server.cpp"
#endif // SERVER_H
