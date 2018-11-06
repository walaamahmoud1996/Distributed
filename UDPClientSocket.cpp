#include "UDPClientSocket.h"

UDPClientSocket::UDPClientSocket ()
{
  if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0) {
  perror("socket failed");
  return;
}
}
/*bool UDPClientSocket::initializeClient (char * _peerAddr, int _peerPort){
  //perhaps add a new client thread
  CSocket.initializeClient ( _peerAddr, _peerPort);
}*/
UDPClientSocket::~UDPClientSocket ( ){

}
