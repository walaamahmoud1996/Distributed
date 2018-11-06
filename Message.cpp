#include "Message.h"



Message::Message(int p_operation,MessageType type, vector<string> p_message, int p_rpc_id){
	message_type = type;
	rpc_id = p_rpc_id;
	operation = p_operation;
	message_size = 0;
	message = p_message;
	for(int i = 0; i < message.size(); i++)
		message_size += message[i].size();
}


Message::Message(string serialized){
		stringstream ss (serialized);
		string t;
		ss >> t;
		message_type = MessageType(stoi(t));
		ss >> t;
		rpc_id = stoi(t);
		ss >> t;
		operation = stoi(t);
		ss >> t;


		message_size = stoi(t);

		char temp;
		ss.get(temp);
		string h = "";
		while(ss.get(temp)){
			//ss.get(temp);
			if (temp == ',') {
				message.push_back(h);
				h = "";
			}
			else h+=temp;
		}

/*
		string message = "";
		char temp;
		for (int i = -1; i<message_size; i++){
			ss.get(temp);
			if(i != -1) message+=temp;
		}
*/
}

string Message::marshal (){
	string serialized = "";
	serialized+= (to_string(int(message_type)) + ' ');
	serialized+= (to_string(rpc_id) + ' ');
	serialized+= (to_string(operation) + ' ');
	serialized+= (to_string(message_size) + ' ');
	for (int i = 0; i < message.size(); i++)
		serialized+= (message[i] + ',');
	return serialized;
}

int Message::getOperation (){

	return operation;
}

int Message::getRPCId(){

	return rpc_id;
}

vector<string> Message::getMessage(){

	return message;
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
void Message::setMessage (vector<string> message, size_t message_size){

	this->message = message;
	this->message_size = message_size;
}
void Message::setMessageType (MessageType message_type){

	this->message_type = message_type;
}
Message::~Message(){}
