#include "Server.h"
using namespace std;

/////private methods defention////////
Message Server::getRequest(){
	char * marshalled_base64;
	int maxBytes = 200; //to be changed
	cout << "ana h2ra aho \n";
	if(udpServerSocket.readSocketWithBlock(marshalled_base64,maxBytes)>0){
		cout << marshalled_base64 << endl;
		std::string x (marshalled_base64);
		Message request_msg(x);

		if(request_msg.getMessageType() == MessageType::Request)
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

Message Server::doOperation(){
	printf("is it assignment problem?");
	Message y(0, Request, "a7eh", 4, 0);
	//Message Z(0, MessageType::Reply, "hi", 3, 0);
	printf("3mlt w rag3");
	return y;
}

void Server::sendReply (Message  _message){
		string str = _message.marshal();
		char* marshalleed_base64 =  strcpy((char*)malloc(str.length()+1),str.c_str());
		int maxBytes = strlen(marshalleed_base64);
		udpServerSocket.writeToSocket(marshalleed_base64, maxBytes);
}





/////public methods defention////////

Server::Server(char * _listen_hostname, int _listen_port){


	if(udpServerSocket.initializeServer(_listen_hostname,_listen_port)){

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
	if(udpServerSocket.isEnabled())
	{
		//listen(udpServerSocket.getSocketHandler(),5);


		Message mp = getRequest();



cout << "I git it \n";
		if(mp.getMessageType()==MessageType::Request)//0 for request 1 for reply
		{
			printf("h3ml 7aga\n");
			Message np = doOperation();
			if(np.getMessageType()==MessageType::Reply)
			{
				printf("hb3t reply");
				sendReply(np);
			}
		}
	}
	else
	{
		cout<<"SERVER Doesn't accept replies"<<endl;
	}

}
Server::~Server(){}
