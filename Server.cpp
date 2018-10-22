#include "Server.h"
#include <thread>

/////private methods defention////////
Message *Server::getRequest(){
	char *marshalled_base64;
	int maxBytes;
	if(udpServerSocket.readFromSocketWithBlock(marshalled_base64,maxBytes)>0){
		Message request_msg(&marshalled_base64);
		if(request_msg.getMessageType==0)
		{

			cout<<"SERVER RECIEVED A REQUEST";
		}
		else
		{
			cout<<"ERROR : SERVER RECIEVED A REPLY";
		}

	}


}
/*
Message *Server::doOperation(){

}
*/
void Server::sendReply (Message * _message){


}





/////public methods defention////////

Server::Server(char * _listen_hostname, int _listen_port){


	if(udpServerSocket->initializeServer(_listen_hostname,_listen_port)){

		cout<<"A SERVER IS INiTILIZED"<<endl;
		udpServerSocket.enable();

		sendReply(getRequest());
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