#ifndef UDPSOCKET_H
#define UDPSOCKET_H
#include"stringMan.h"
#include<string>
#include<cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include<stdio.h>
#include <netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include <arpa/inet.h>
#define SIZE 8000
using namespace	std;

class UDPSocket
{
protected:
	int sock;
	struct sockaddr_in myAddr,peerAddr;
	//sockaddr_in peerAddr;
	char * myAddress;
	char * peerAddress;
	int myPort;
	int peerPort;
	bool enabled;
	pthread_mutex_t mutex;

	void Close_Socket();

	void makeDestSA(char * hostname);

	int startUp();
	int acceptConnection();
	void makeReceiverSA(struct sockaddr_in *sa, int port);
	void makeLocalSA(struct sockaddr_in *sa);
	void makeDestSA(struct sockaddr_in * sa, char *hostname, int port);


public:
	UDPSocket ();
	// void setFilterAddress (char * _filterAddress);
	// char * getFilterAddress ();
	struct sockaddr_in getPeerAddr(string& hostname, int& port);
	void setPeerAddr(struct sockaddr_in);
	void setPeerAddr(string, int);
	bool initializeServer (char * _myAddr, int _myPort);
	bool initializeClient (char * _peerAddr, int _peerPort);
	int writeToSocket (char * buffer, int maxBytes );//for a reply a server side function
	int writeToSocketAndWait (char * buffer, int maxBytes, int Sec ,int microSec, string& rMessage );//for a request a client side function
	int readFromSocketWithNoBlock (char * buffer, int maxBytes);//recieve from a client// server side function //nonblocking recieve
	int readFromSocketWithTimeout (string& buffer, int maxBytes, int timeoutSec,
	int timeoutMicro);// a server side function
	//int readFromSocketWithBlock (char * buffer, int maxBytes );//a client side function
	int readSocketWithNoBlock (char * buffer, int maxBytes );//read from a server // aclinet side function
	int readSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int
	timeoutMicro);
	int readSocketWithBlock (string& buffer, int maxBytes );
	int getMyPort ();
	int getPeerPort ();
	void enable();
	void disable();
	bool isEnabled();
	void lock();
	void unlock();
	int getSocketHandler();
	~UDPSocket ( );
};

#endif // UDPSOCKET_H
