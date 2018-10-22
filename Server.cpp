#include "Server.h"
#include <thread>

/////private methods defention////////
Message *Server::getRequest(){
	int nRead;
	Message buf[SIZE],*p=buf;
	nRead = 0;

	if(amount)

}
Message *Server::doOperation(){

}
void Server::sendReply (Message * _message){

	this->message_type = Reply;
	_message.setMessageType(this->message_type);


}





/////public methods defention////////

Server::Server(char * _listen_hostname, int _listen_port){


	if(udpServerSocket->initializeServer(_listen_hostname,_listen_port)){

		cout<<"SERVER SOCKET IS CREATED"<<endl;
		udpServerSocket.enable();
	}
	else
	{
		cout<<"ERROR:: Server cannot be intialized"<<endl;
		udpServerSocket.disable();
	}
}



//should be blocking 
void Server::serveRequest(){
	if(udpServerSocket.isEnable())
	{
		//listen(udpServerSocket.getSocketHandler(),5);
		Message*mp = getRequest();
		if(mp->getMessageType()==0)//0 for request 1 for reply
		{
			mp = doOperation(mp->getOperation());
			if(mp->getMessageType())//1 for reply
			{
				sendReply(mp->getMessage());
			}
		}
	}
	else
	{
		cout<<"SERVER IS DOWN"<<endl;
	}

}
Server::~Server(){}