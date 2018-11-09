#ifndef CLIENT_H
#define CLIENT_H
#include <map>

#include "UDPClientSocket.h"
#include "Message.h"
#include "Image.h"
//enum MessageType {Request,Reply};
enum operations{login,Take_my_recource,give_me_images_lables,ping,register_request,ask_for_qouta,update_qouta,request_statistics};
class Client
{
private:
	UDPClientSocket udpSocket;
	char * hostname;
	int recv_port;
	int send_port;
	string username;
	string password;
	int rpc_id;

	map<string,string> name_to_image;
	map<string,int> image_to_qouta;
	vector<string> images_to_see;
	

	void ProcessText(string);

	//void CommunicationModule();
	/*
		*sends the marshaled message created by the stub
		*recieves a reply from server and unmarshal it
	*/
	//Message * doOperation(int operationID);
	/*
		client side function uses time out
	parameters
		*remote reference IP address + a port number
		*operation ID
		*arguments array of bytes
	issues a send function - sends a request
	issues a recieve to get the reply uses a time out if there were no reply
	options for timeout
		* return with indication the doOperation has failed
		*
	request_messag would be of this structure

		Message Type
		requestID //should be unique for the client
		remoteRefenece
		operationID
		arquments

	*/
	

	int getPacketNumber(string message, bool& end);
	pair<string,int>owner_address;
	string Client_Token;

public:
	Client(char * _hostname, int _port);
	Client();
	Message  execute(Message  _message);

	//Client();
	//Request Functions From Directory
	void Take_my_recources(string);
	void Login(string,string);
	void Give_me_images();
	void Ping();
	bool Is_Online(string username);

	//Request Functions From Peers
	void Ask_for_qouta(string owner_name,string image_name);
	void Update_qouta(int new_qouta);
	void Request_statistics(string image_name);
	//Frontend Functions
	void Upload_Image(string image_name);
	void View_Image(string);
	~Client();
};
//#include "Client.cpp"
#endif // CLIENT_H