#ifndef UDPSERVERSOCKET_H
#define UDPSERVERSOCKET_H
#include "UDPSocket.h"

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

class UDPServerSocket : public UDPSocket
{
public:
	UDPServerSocket ();
	//bool initializeServer (char * _myAddr, int _myPort);
	//~UDPServerSocket ();
};
//#include "UDPServerSocket.cpp"
#endif // UDPSERVERSOCKET_H
