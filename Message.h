#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <cstring>

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#define SIZE 8000

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
	int arg_num;

public:
	Message(int p_operation,MessageType type, vector<string> p_message,int p_rpc_id);
	Message(vector<string> marshalled_base64);
	vector<string> marshal ();
	int getOperation ();
	int getRPCId();
	string ShrinkInt(int x);
	int UnShrinkInt(string tmp);
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
