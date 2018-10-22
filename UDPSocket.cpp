#include "UDPSocket.h"
#include "rpc/clinet.h"

UDPSocket::UDPSocket (){
	
}
}
void UDPSocket::setFilterAddress (char * _filterAddress);
char * UDPSocket::getFilterAddress ();
bool UDPSocket::initializeServer (char * _myAddr, int _myPort){

	this->myAddress = _myAddr;
	this->myPort = _myPort;

	this->myAddr->sinfamily = AF_INET;
	this->myAddr->sin_port = htons(myPort);
	this->myAddr->sing_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sock,&myAddr,sizeof(struct sockaddr_in))!=0){

		perror("ERROR : BIND FAILED IN INTIALIZING A SERVER")
		close(sock);
		return false;
	}
	else
		return true;
}
bool UDPSocket::initializeClient (char * _peerAddr, int _peerPort){
	 this->peerAddress = _peerAddr;
	 this->peerPort = _peerPort;

	 this->myAddr->sinfamily = AF_INET;
	 this->myAddr->sinport = htons(0);
	 this->myAddr->sing_addr.s_addr = htonl(INADDR_ANY);
	 if(bind(sock,&myAddr,sizeof(struct sockaddr_in))!=0){

		perror("ERROR : BIND FAILED IN INTIALIZING A CLIENT")
		close(sock);
		return false;
	}
	else
		return true;



	

	


}
int UDPSocket::writeToSocket (char * buffer, int maxBytes ){
	/*this is for sending a reply from server*/
	int bytesnum;
	struct hostent *host;
	this->peerAddr->sinfamily = AF_INET;
	if((host = gethostbyname(peerAddress))==NULL){

		printf("Unknonw host name\n");
		exit(-1);
	}


	this->peerAddr->sin_addr = *(stuct in_addr*)(host->h_addr);
	this->peerAddr->sin_port = htons(this->peerPort);


	if(bytesnum = sendto(this->sock,buffer,sizeof(buffer),0,peerAddr,sizeof(struct sockaddr_in)))<0)
		{
			perror("ERROR : CANNOT SEND A REPLY TO CLIENT");
		}

	return bytesnum;

}
int UDPSocket::writeToSocketAndWait (char * buffer, int maxBytes,int microSec ){

	/*this is for sending a request from a client waiting for a reply from a server*/
}
int UDPSocket::readFromSocketWithNoBlock (char * buffer, int maxBytes ){
	
	

}
int UDPSocket::readFromSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec,
int timeoutMilli);//this is a client side method
int UDPSocket::readFromSocketWithBlock (char * buffer, int maxBytes ){
	int bytesnum,aLenght;
	aLenght = sizeof(this->peerAddr);
	this->peerAddr.sinfamily = AF_INET;
	if(bytesnum=recvfrom(this->sock,buffer,SIZE,0,&peerAddr,&aLenght)<0){
		perror("ERROR :SERVER CANNOT RECIEVE");
		return bytesnum;
	}
	else
		if(bytesnum>maxBytes)
		{
			perror("ERROR :SERVER SOCKET OVERFLOW");
			return 0;
		}
	else
		return bytesnum;	

}
int UDPSocket::readSocketWithNoBlock (char * buffer, int maxBytes );
int UDPSocket::readSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int
	timeoutMilli);
int UDPSocket::readSocketWithBlock (char * buffer, int maxBytes );
int UDPSocket::getMyPort ();
int UDPSocket::getPeerPort ();
void UDPSocket::enable(){
	enabled = true;
}
void UDPSocket::disable(){
	enabled = false;
}
bool UDPSocket::isEnabled(){

	return enabled;
}
void UDPSocket::lock();
void UDPSocket::unlock();
int UDPSocket::getSocketHandler();
UDPSocket::~UDPSocket ( );