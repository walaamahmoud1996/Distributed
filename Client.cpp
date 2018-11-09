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
	cout << "number of packets: "<<str.size() << endl;
	for(int i =0; i < str.size(); i++)
	{
		char* buffer = copyStr(str[i]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
		// string tmpS ="";
		// for(int zv =12;zv<16;zv++)
		// 	tmpS.push_back(buffer[zv]);
		// cout << "\npacket is: " << (UnShrinkInt(tmpS) & 0x7fffffff) << endl;
		// cout << "\nis it the end?" << ((buffer[15] >>7)&1) << endl;
		maxBytes = str[i].size();
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
		else if(udpSocket.writeToSocketAndWait(buffer,maxBytes, 3 ,0, rMessage) >= 0)	//something is recieved;
		{
			vector<string> tmp;
			tmp.push_back(rMessage);
			Message X(tmp);
			// cout << "X Operation: " << X.getOperation() << endl;
			// cout << "Arg_Num: " << X.getArgNum() << endl;

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

	cout << "I'll be recieving now\n";
	//now you're ready to recieve the reply;
	bool isEnd = true;
	int cnt = 0;
	vector<string> Recieved;
	while(isEnd)
	{
		string rMessage;
		int packet;
		if(udpSocket.readFromSocketWithTimeout(rMessage, SIZE,3,0) >= 0)
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
		//		char* buffer = strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
				char* buffer = copyStr(tmp[0]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());

				maxBytes = tmp[0].size();
				udpSocket.writeToSocketAndWait(buffer, maxBytes,0,0,rMessage);
			}
	}
	vector<string> tmp;
	tmp.push_back("g");
	Message Packet1440(1440,MessageType::Reply,tmp,_message.getRPCId());
	Packet1440.setArgNum(0);
	tmp = Packet1440.marshal();
	//char* buffer = strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
	char* buffer = copyStr(tmp[0]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());

	maxBytes = tmp[0].size();
	udpSocket.writeToSocketAndWait(buffer, maxBytes,0,0,rMessage);

	Message Returned(Recieved);
	return Returned;
}
Client::~Client(){}
