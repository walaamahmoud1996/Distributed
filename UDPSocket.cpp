 #include "UDPSocket.h"
using namespace std;
UDPSocket::UDPSocket (){

}

void UDPSocket::setFilterAddress (char * _filterAddress){

}
char * UDPSocket::getFilterAddress (){

}
void UDPSocket::makeReceiverSA(struct sockaddr_in *sa, int port)
{
sa->sin_family = AF_INET;
sa->sin_port = htons(port);
sa-> sin_addr.s_addr = htonl(INADDR_ANY);
}
bool UDPSocket::initializeServer (char * _myAddr, int _myPort){
	this->myAddress = _myAddr;
	this->myPort = _myPort;

	makeReceiverSA(&myAddr,myPort);

	if(bind(sock,(struct sockaddr *)&myAddr,sizeof(struct sockaddr_in))!=0){

		perror("ERROR : BIND FAILED IN INTIALIZING A SERVER");
		//close(sock);
		return false;
	}
	else
		return true;
}

void UDPSocket::makeLocalSA(struct sockaddr_in *sa)
{
sa->sin_family = AF_INET;
sa->sin_port = htons(0);
sa-> sin_addr.s_addr = htonl(INADDR_ANY);
}

bool UDPSocket::initializeClient (char * _peerAddr, int _peerPort){
	 this->peerAddress = _peerAddr;
	 this->peerPort = _peerPort;


	 makeLocalSA(&myAddr);
	 if(bind(sock,(struct sockaddr *)&myAddr,sizeof(struct sockaddr_in))!=0){

		perror("ERROR : BIND FAILED IN INTIALIZING A CLIENT");
		close(sock);
		return false;
	}
	else
		return true;
}
void UDPSocket::makeDestSA(struct sockaddr_in * sa, char *hostname, int port)
{
struct hostent *host;
sa->sin_family = AF_INET;
if((host = gethostbyname(hostname))== NULL){
  printf("Unknown host name\n");
  exit(-1);
}
  sa-> sin_addr = *(struct in_addr *) (host->h_addr);
  sa->sin_port = htons(port);
}
int UDPSocket::writeToSocket (char * buffer, int maxBytes ){
	/*this is for sending a reply from server*/
	int bytesnum;

	//makeDestSA(&peerAddr,this->peerAddress,this->peerPort);

  cout << "hb3t 5alas a5er kalam\n";
	if((bytesnum = sendto(this->sock,buffer,strlen(buffer),0,(struct sockaddr *)&peerAddr,sizeof(struct sockaddr_in)))<0)
		{
			perror("ERROR : CANNOT SEND A REPLY TO CLIENT");
		}

	return bytesnum;
}

int UDPSocket::writeToSocketAndWait (char * buffer, int maxBytes,int Sec,int microSec ){

	/*this is for sending a request from a client waiting for a reply from a server*/
	int bytesnum;
	struct hostent *host;
	makeDestSA(&peerAddr,this->peerAddress,this->peerPort);

  //cout << buffer <<endl;
  //cout << strlen(buffer) <<endl;

	if((bytesnum = sendto(this->sock,buffer,strlen(buffer),0,(struct sockaddr *)&peerAddr,sizeof(struct sockaddr_in)))<0)
		{
			perror("ERROR : CANNOT SEND A REPLY TO CLIENT");
		}
    cout << buffer <<endl;

	//return bytesnum;

  string message;
	return readFromSocketWithTimeout(message,maxBytes,Sec,microSec);


}
int UDPSocket::readFromSocketWithNoBlock (char * buffer, int maxBytes ){

	//same design as blocking but with thread for each client
return 1;
}
int UDPSocket::readFromSocketWithTimeout (string& buffer, int maxBytes, int timeoutSec,int timeoutMicro)//this is a client side method
{
	int bytesnum;
  char message1[SIZE];
  memset(message1,0 ,sizeof(message1));

	socklen_t aLenght = sizeof(this->peerAddr);
	peerAddr.sin_family = AF_INET;
	struct timeval tv;
  tv.tv_usec = timeoutMicro;
  tv.tv_sec = timeoutSec;
  if (setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
      perror("Error");
     	return -1;
  }
  else if((bytesnum=recvfrom(this->sock,message1,SIZE,0,(struct sockaddr *)&peerAddr,&aLenght)<0)){
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
  {
    buffer = message1;
    cout << buffer << endl;
		return bytesnum;
  }
}

int UDPSocket::readSocketWithBlock (string& buffer, int maxBytes ){
	int bytesnum;

	socklen_t aLenght = sizeof(this->peerAddr);
	peerAddr.sin_family = AF_INET;
	printf("wallahi h2ra\n");
  char message1[SIZE];
  memset(message1,0 ,sizeof(message1));
	if((bytesnum=recvfrom(sock,message1,SIZE,0,(struct sockaddr *)&peerAddr,&aLenght)<0)){
    printf("you don't listen\n");
		perror("ERROR :SERVER CANNOT RECIEVE");
    return bytesnum;
	}
	else if(bytesnum>maxBytes)
		{
			perror("ERROR :SERVER SOCKET OVERFLOW");
			return 0;
		}
	else
  {
    for(int i =0; i< SIZE; i++)
      cout << message1[i];
    buffer = message1;
    cout << buffer <<endl;
    cout << bytesnum << endl;
		return bytesnum;
  }
}
int UDPSocket::readSocketWithNoBlock (char * buffer, int maxBytes ){

}
int UDPSocket::readSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int
	timeoutMicro)
{
	int bytesnum;
	socklen_t aLenght = sizeof(this->peerAddr);
	this->peerAddr.sin_family = AF_INET;
	struct timeval tv;
      tv.tv_usec = timeoutMicro;
      tv.tv_sec = timeoutSec;
    if (setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
        perror("Error");
        //msg = "Error123";
      return -1;
      }
    else
	if((bytesnum=recvfrom(this->sock,buffer,SIZE,0,(struct sockaddr *)&peerAddr,&aLenght))<0)
	{
		perror("ERROR :SERVER CANNOT RECIEVE");
		return bytesnum;
	}

	/*else
	{
		/*struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&aSocketAddress;
        struct in_addr ipAddr = pV4Addr->sin_addr;
        char str[INET_ADDRSTRLEN];
        inet_ntop( AF_INET, &ipAddr, this->peerAddress, INET_ADDRSTRLEN );
		return bytesnum;
	}*/



}
//int UDPSocket::readSocketWithBlock (char * buffer, int maxBytes );
int UDPSocket::getMyPort (){

	return this->myPort;
}
int UDPSocket::getPeerPort (){
	return this->peerPort;
}
void UDPSocket::enable(){
	enabled = true;
}
void UDPSocket::disable(){
	enabled = false;
}
bool UDPSocket::isEnabled(){

	return enabled;
}
void UDPSocket::lock(){

//for threading
	}
void UDPSocket::unlock(){
	//for threading
}
int UDPSocket::getSocketHandler(){
	return this->sock;
}
UDPSocket::~UDPSocket ( ){
	close(this->sock);

}
