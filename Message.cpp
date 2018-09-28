#include "Message.h"




Message::Message(int operation, void * p_message, size_t p_message_size,int p_rpc_id){}



Message::Message(char * marshalled_base64){}
char *Message::marshal (){}
int Message::getOperation (){

	return operation;
}
int Message::getRPCId(){

	return rpc_id;
}
void *Message::getMessage(){

	return messaeg;
}
size_t Message::getMessageSize(){

	return message_size;
}
MessageType Message::getMessageType(){

	return message_type;
}
void Message::setOperation (int _operation){

	this->operation = _operation;
}
void Meassage::setMessage (void * message, size_t message_size){

	this->message = message;
}
void Message::setMessageType (MessageType message_type){

	this->message_type = message_type;
}
Message::~Message();