#ifndef UDPCLIENTSOCKET_H
#define UDPCLIENTSOCKET_H
class UDPClientSocket : public UDPSocket
{
public:
	UDPClientSocket ();
	bool initializeClient (char * _peerAddr, int _peerPort);
	~UDPClientSocket ( );
};
#include "UDPClientSocket.cpp"
#endif // UDPCLIENTSOCKET_H