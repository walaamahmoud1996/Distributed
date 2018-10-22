#include "Message.h"




Message::Message(int operation,MessageType type, void * p_message, size_t p_message_size,int p_rpc_id){
	
	this->operation = operation;
	this->message_type = type;
	this->message = p_message;
	this->message_size = p_message_size;
	this->rpc_id = p_rpc_id;

}




Message::Message(char * marshalled_base64){
	/*
		unmarshal message

	*/
}
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
	this->message_size = message_size;
}
void Message::setMessageType (MessageType message_type){

	this->message_type = message_type;
}
Message::~Message();