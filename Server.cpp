#include "Server.h"
using namespace std;

/////private methods defention////////
Message Server::getRequest(){
	char * marshalled_base64;
	int maxBytes = 200; //to be changed
	cout << "ana h2ra aho \n";
	if(udpServerSocket.readSocketWithBlock(marshalled_base64,maxBytes)>0){
		//cout << marshalled_base64 << endl;
		cout << "read and filling the message\n";
		Message request_msg(string(marshalled_base64));
		cout << string(marshalled_base64)<<endl;
		/*if(request_msg.getMessageType() == MessageType::Request)
		{

			cout<<"SERVER RECIEVED A REQUEST";
			return request_msg;
		}
		else
		{
			cout<<"ERROR : SERVER RECIEVED A REPLY";
		}
*/
	}


}

Message Server::doOperation(){
	Message ms(1, Reply, "hi", 2,1);
	return ms;
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
			mp = doOperation();
			if(mp.getMessageType()==MessageType::Request)//0 for request
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
