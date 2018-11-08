#include "Client.h"


Client::Client(char * _hostname, int _port)
{
	rpc_id=0;

	if(udpSocket.initializeClient(_hostname,_port)){
		cout <<"Client in intialized\n";
		udpSocket.enable();
	}
	else
		cout<<"Failed To intialize a Client\n";



}
Client::Client(){

}
/////// send a message and returns a reply //////////
/*Message* Client::execute(Message _message){

	int maxBytes = _message.getMessageSize();
	string str = (_message.marshal());
	cout << str << endl;
	char* buffer = strcpy((char*)malloc(str.length()+1),str.c_str());
	cout << buffer << endl;
	udpSocket.writeToSocketAndWait(buffer,maxBytes,3,0);

}*/

void Client::Upload_Image(string image_name){

	Image newImage(image_name+".jpeg",image_name+".txt");

}

void Client::Login(string user_name,string password){
	vector<string> login_p;
	login_p.push_back(user_name);
	login_p.push_back(password);
	rpc_id++;


	Message login_message(int(login),Request,login_p,rpc_id);
	
	

}
Client::~Client(){}
