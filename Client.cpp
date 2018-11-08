#include "Client.h"

Client::Client(char * _hostname, int _port)
{
	hostname = _hostname;
	send_port = _port;

	if(udpSocket.initializeClient(_hostname,_port)){
		cout <<"Client in intialized\n";
		udpSocket.enable();
	}
	else
		cout<<"Failed To intialize a Client\n";



}

int Client::UnShrinkInt(string tmp)
{
  int x = 0;
  for(int i =0; i < 4;i++)
  {
    int tmpx = tmp[i] &0xff;
    x |= (tmpx<<(i*8));
  }
  return x;

}

int Client::getPacketNumber(string message, bool& end)
{
	int tmp = UnShrinkInt(message.substr(12,4));

	end = (tmp >> 31);
	tmp &= 0x7fffffff;
	return tmp;
}

/////// send a message and returns a reply //////////
Message Client::execute(Message _message){

	int maxBytes = _message.getMessageSize();
	vector<string> str = (_message.marshal());
	//cout << str << endl;
	string rMessage = "";
	for(int i =0; i < str.size(); i++)
	{
		char* buffer = strcpy((char*)malloc(str[i].length()+1),str[i].c_str());
		//cout << buffer << endl;
		if(i != str.size()-1)
		{
			if(udpSocket.writeToSocketAndWait(buffer,maxBytes, 0, 3, rMessage) == 0)	//something is recieved;
			{
				vector<string> tmp;
				tmp.push_back(rMessage);
				Message X(tmp);
				if(X.getOperation() == 1440)
				{
					vector<string> tmp1 = X.getMessage();
					i = stoi(tmp1[0]) - 1;
				}
			}
		}
		else if(udpSocket.writeToSocketAndWait(buffer,maxBytes, 3 ,0, rMessage) == 0)	//something is recieved;
		{
			vector<string> tmp;
			tmp.push_back(rMessage);
			Message X(tmp);
			if(X.getOperation() == 1440)
			{
				if(X.getArgNum() == 1)
				{
					vector<string> tmp1 = X.getMessage();
					i = stoi(tmp1[0]) - 1;
				}
			}
		}
		else
		{
			i = -1;
		}
	}


	//now you're ready to recieve the reply;
	bool isEnd = true;
	int cnt = 0;
	vector<string> Recieved;
	while(isEnd)
	{
		string rMessage;
		int packet;
		if(udpSocket.readFromSocketWithTimeout(rMessage, SIZE,3,0) < 0)
			packet = getPacketNumber(rMessage, isEnd);
		else
			packet = -1;

		if(packet == cnt)
		{
			cnt++;
			Recieved.push_back(rMessage);
		}
		else
			{
				vector<string> tmp;
				tmp.push_back(to_string(cnt));
				Message Packet1440(1440,MessageType::Reply,tmp,_message.getRPCId());
				tmp = Packet1440.marshal();
				char* buffer = strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
				udpSocket.writeToSocketAndWait(buffer, maxBytes,0,0,rMessage);
			}
	}
	vector<string> tmp;
	Message Packet1440(1440,MessageType::Reply,tmp,_message.getRPCId());
	tmp = Packet1440.marshal();
	char* buffer = strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
	udpSocket.writeToSocketAndWait(buffer, maxBytes,0,0,rMessage);

	Message Returned(Recieved);
	return Returned;
}
Client::~Client(){}
