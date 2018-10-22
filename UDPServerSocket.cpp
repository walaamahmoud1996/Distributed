#include "UDPServerSocket.h"

UDPServerSocket::UDPServerSocket()
{
	if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0) {
	perror("socket failed");
	return;
}
bool UDPServerSocket::initializeServer (char * _myAddr, int _myPort){

}
UDPServerSocket::~UDPServerSocket ( ){
	
}