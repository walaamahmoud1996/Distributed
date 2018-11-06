#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <cstring>

#include <iostream>
#include <sstream>
#include <vector>


using namespace std;
enum MessageType {Request, Reply};
class Message
{
private:
	MessageType message_type;
	int operation;
	vector <string> message;
	size_t message_size;
	int rpc_id;


public:
	Message(int p_operation,MessageType type, vector<string> p_message,int p_rpc_id);
	Message(string marshalled_base64);
	string marshal ();
	int getOperation ();
	int getRPCId();
	vector<string> getMessage();
	size_t getMessageSize();
	MessageType getMessageType();
	void setOperation (int _operation);
	void setMessage (vector<string> message, size_t message_size);
	void setMessageType (MessageType message_type);
	~Message();
	/*

		RPC messages

	*/

};
//#include "Message.cpp"
#endif // MESSAGE_H
