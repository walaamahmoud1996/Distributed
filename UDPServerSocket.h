#ifndef UDPSERVERSOCKET_H
#define UDPSERVERSOCKET_H



class UDPServerSocket : public UDPSocket
{
public:
	UDPServerSocket ();
	bool initializeServer (char * _myAddr, int _myPort);
	~UDPServerSocket ( );
};
#include "UDPServerSocket.cpp"
#endif // UDPSERVERSOCKET_H