#include "Message.h"



Message::Message(int p_operation,MessageType type, vector<string> p_message, int p_rpc_id){
	message_type = type;
	rpc_id = p_rpc_id;
	operation = p_operation;
	message_size = 0;
	message = p_message;
	for(int i = 0; i < message.size(); i++)
		message_size += message[i].size()+1;
	arg_num = message.size();
	message_size -= 1;
}


Message::Message(vector<string> serialized){
	arg_num = -1;		//if arg_num = -1; then this is a phantom message;
	message_size = 0;
	MessageType message_type;
	operation = -1;
	rpc_id = -1;
	string messageSent = "";
	for(int i = 0; i < serialized.size();i++)
	{
		int tmpx;
		tmpx = UnShrinkInt(serialized[i].substr(0,4));
		if(i== 0)
			rpc_id = tmpx;
		else if(rpc_id != tmpx)
		{
			arg_num = -1;
			break;
		}

		tmpx = UnShrinkInt(serialized[i].substr(4,4));
		if(i ==0)
			{
				operation = tmpx & 0x7fffffff;
				message_type = MessageType(tmpx >> 31);
			}
		else if((operation != (tmpx & 0x7fffffff))||(message_type != MessageType(tmpx >> 31)))
		{
			arg_num = -1;
			break;
		}
		tmpx = UnShrinkInt(serialized[i].substr(8,4));
		if(i == 0)
		{
			message_size += (tmpx &0x00ffffff);
			arg_num = (tmpx >> 24) &0xff;
		}
		else if(arg_num != ((tmpx >> 24) &0xff))
		{
			arg_num = -1;
			break;
		}
		messageSent += serialized[i].substr(12,SIZE-16);


	}

		int To = 0;
		for(int i =0; i < arg_num-1; i++)
		{
			size_t found = messageSent.find(' ');
			string t = messageSent.substr(To,found);

			To += (found+1);
			message.push_back(t);
		}
		string t = messageSent.substr(To,messageSent.size());
		message.push_back(t);
}


string Message::ShrinkInt(int x)
{
	string returned = "";
	for(int i =0; i < 4; i++)
	{
		char z = x & 0xff;
    cout << z<< endl;
		returned.push_back(z);
		x = x>>8;
	}
	return returned;
}

int Message::UnShrinkInt(string tmp)
{
  int x = 0;
  for(int i =0; i < 4;i++)
  {
    int tmpx = tmp[i] &0xff;
    x |= (tmpx<<(i*8));
  }
  return x;

}

vector <string> Message::marshal (){
	string messageSent = "";
	for(int i=0; i < message.size();i++)
	{
		if(i != message.size()-1)
			messageSent += message[i] + ' ';
		else
			messageSent += message[i];
	}

	vector<string> serialized;
	int end = ceil(message_size/float(SIZE-16));


	for(int i = 0; i < end;i++)
	{
		string tmp = "";
		tmp += ShrinkInt(rpc_id);


		operation &= 0x7fffffff;
		tmp+= ShrinkInt((int(message_type)<<31) | operation);

		if(i!=end-1)
			tmp+= ShrinkInt( (arg_num<<24) | SIZE-16);		//remove this in the near future
		else
			tmp+= ShrinkInt((arg_num<<24) | message_size%(SIZE-16));


		tmp += ShrinkInt(((i!=(end-1))<<31)|(i&0x7fffffff));


		tmp += messageSent.substr(i*(SIZE-16),SIZE-16);

		serialized.push_back(tmp);
	}
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
