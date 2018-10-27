#ifndef MESSAGE_H
#define MESSAGE_H
enum MessageType {Request, Reply};
class Message
{
private:
	MessageType message_type;
	int operation;
	string message;
	size_t message_size;
	int rpc_id;


public:
	Message(int operation, string p_message, size_t p_message_size,int p_rpc_id);
	Message(char * marshalled_base64);
	string marshal ();
	int getOperation ();
	int getRPCId();
	string getMessage();
	size_t getMessageSize();
	MessageType getMessageType();
	void setOperation (int _operation);
	void setMessage (string message, size_t message_size);
	void setMessageType (MessageType message_type);

	/*

		RPC messages

	*/
	~Message();
};
#include "Message.cpp"
#endif // MESSAGE_H
