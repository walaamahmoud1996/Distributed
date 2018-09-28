#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



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
	void Create_Socket();
	void Close_Socket();
	void makeLocalSA();
	void makeDestSA();



public:
	UDPSocket ();
	void setFilterAddress (char * _filterAddress);
	char * getFilterAddress ();
	bool initializeServer (char * _myAddr, int _myPort);
	bool initializeClient (char * _peerAddr, int _peerPort);
	int writeToSocket (char * buffer, int maxBytes );
	int writeToSocketAndWait (char * buffer, int maxBytes,int microSec );
	int readFromSocketWithNoBlock (char * buffer, int maxBytes );
	int readFromSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec,
	int timeoutMilli);
	int readFromSocketWithBlock (char * buffer, int maxBytes );
	int readSocketWithNoBlock (char * buffer, int maxBytes );
	int readSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int
	timeoutMilli);
	int readSocketWithBlock (char * buffer, int maxBytes );
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
#include "UDPSocket.cpp"
#endif // UDPSOCKET_H		