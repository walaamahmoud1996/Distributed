#include "Server.h"


/////private methods defention////////
Message *Server::getRequest(){}
Message *Server::doOperation(){}
void Server::sendReply (Message * _message){

	this->message_type = Reply;
	_message.setMessageType(this->message_type);


}





/////public methods defention////////

Server::Server(char * _listen_hostname, int _listen_port){


	if(udpServerSocket->initializeServer(_listen_hostname,_listen_port)){

		
	}
}




void Server::serveRequest(){}
Server::~Server(){}