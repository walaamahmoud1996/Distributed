#include "UDPSocket.h"



UDPSocket::UDPSocket (){}


//////private functions defintions////
void UDPSocket::CloseSocket(){
	close(sock);
}

void UDPSocket::CreateSocket(char* machine_name){

	if(( this->sock = socket(AF_INET, SOCK_DGRAM, 0))<0) {
		perror("socket failed");
		return;
	}	
	makeLocalSA();
	if( bind(s, &myAddr, sizeof(struct sockaddr_in))!= 0){
		perror("Bind failed\n");
		Close_Socket(this->sock);
		return;
	}

	makeDestSA(machine_name);
}

void UDPSocket::makeLocalSA(){

	this->myAddr->sin_family = AF_INET;
	this->myAddr->sin_port = htons(0);
	this->myAddr->sin_addr.s_addr = htonl(INADDR_ANY);
}
void UDPSocket::makeDestSA(char * hostname){
	struct hostent *host;
	this->peerAddr->sin_family = AF_INET;
	if((host = gethostbyname(hostname))== NULL){
	printf("Unknown host name\n");
	exit(-1);
	}
	this->peerAddr->sin_addr = *(struct in_addr *) (host->h_addr);
	this->peerAddr->sin_port = htons(this->peerPort);


}


//////public functions defintions////

void UDPSocket::setFilterAddress (char * _filterAddress){}
char *UDPSocket::getFilterAddress (){}
bool UDPSocket::initializeServer (char * _myAddr, int _myPort){

	this->myAddress = _myAddr;
	this->myPort = _myPort;
	this->myAddress = _myAddr;
	this->myPort = _myPort;
}

bool UDPSocket::initializeClient (char * _peerAddr, int _peerPort){

	this->peerAddress = _peerAddr;
	this->peerPort = _peerPort;}
int UDPSocket::writeToSocket (char * buffer, int maxBytes ){}
int UDPSocket::writeToSocketAndWait (char * buffer, int maxBytes,int microSec ){}
int UDPSocket::readFromSocketWithNoBlock (char * buffer, int maxBytes ){}
int UDPSocket::readFromSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec,
timeoutMilli){}
int UDPSocket::readFromSocketWithBlock (char * buffer, int maxBytes ){}
int UDPSocket::readSocketWithNoBlock (char * buffer, int maxBytes ){}
int UDPSocket::readSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int
	timeoutMilli){}
int UDPSocket::readSocketWithBlock (char * buffer, int maxBytes ){}


/* Return the sender port number*/
int UDPSocket::getMyPort (){

	return myPort;}
/* Return the reviever port number*/
int UDPSocket::getPeerPort (){

	return peerPort;}
/*Enable the Socekt*/
void UDPSocket::enable(){
	
	this->enabled = true;}
/*Disable the Socket*/
void UDPSocket::disable(){
	
	this->enabled = false;}
/*Check if the Socket is Enabled_return true or Disabled_return false*/
bool UDPSocket::isEnabled(){

	return enabled;}

void UDPSocket::lock(){}
void UDPSocket::unlock(){}
int UDPSocket::getSocketHandler(){}
UDPSocket::~UDPSocket ( ){}