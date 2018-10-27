#include "Server.h"
#include"Message.h"
#include<cstring>
#include <thread>
using namespace std;

/////private methods defention////////
Message *Server::getRequest(){
	char *marshalled_base64;
	int maxBytes = 200; //to be changed
	if(udpServerSocket.readSocketWithBlock(marshalled_base64,maxBytes)>0){
		Message request_msg(&marshalled_base64);

		if(request_msg.getMessageType()==0)
		{

			cout<<"SERVER RECIEVED A REQUEST";
			return request_msg;
		}
		else
		{
			cout<<"ERROR : SERVER RECIEVED A REPLY";
		}

	}


}

Message *Server::doOperation(){
	Message ms(1,string, "hi", 2,1)
	return ms;
}

void Server::sendReply (Message * _message){
		char* marshalleed_base64 =  message.marshal();
		int maxBytes = strlen(marshalleed_base64);
		UDPServerSocket.writeToSocket(marshalleed_base64, maxBytes);
}





/////public methods defention////////

Server::Server(char * _listen_hostname, int _listen_port){


	if(udpServerSocket->initializeServer(_listen_hostname,_listen_port)){

		cout<<"A SERVER IS INiTILIZED"<<endl;
		udpServerSocket.enable();

	//	sendReply(getRequest());
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
			mp = doOperation();
			if(!mp->getMessageType())//0 for request
			{
				sendReply(mp);
			}
		}
	}
	else
	{
		cout<<"SERVER Doesn't accept replies"<<endl;
	}

}
Server::~Server(){}
