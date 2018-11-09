#include "Server.h"
using namespace std;




int Server::getPacketNumber(string message, bool& end)
{
	int tmp = UnShrinkInt(message.substr(12,4));
  end = (tmp >> 31) & 1;
  tmp &= 0x7fffffff;
	return tmp;
}



bool Server::matchPackets(string Packet1)
{
//  cout << "operation & MT: " << UnShrinkInt(Packet1.substr(4,4)) << endl;
	int rpc_id1 = UnShrinkInt(Packet1.substr(0,4));
	//cout << "rpc: " << rpc_id1 << endl;
	string hostname;
	int port;
	struct sockaddr_in targetAddr = udpServerSocket.getPeerAddr(hostname, port);
	pair<pair<string, int>, int> Index = make_pair(make_pair(hostname,port),rpc_id1);		// you can't use sockaddr_in because it doesn't have a less than operator defined so no map; instead use port and hostname to build a unique map of pair<pair<int,int>, int>, vector<string>
	bool lastPacketFlag = false;
	vector<string >tmp;
//	Log[ make_pair(Addr,rpc_id1)] = tmp;
	if(Log.count(Index))
	{
		string tmp = Log[Index][Log[Index].size() - 1];
		int lastPacket = getPacketNumber(tmp, lastPacketFlag);
		int packet = getPacketNumber(Packet1, lastPacketFlag);
    // cout << "current Packet: " << packet <<endl;
    // cout << "Is it the last? " << lastPacketFlag << endl;
		if( (lastPacket+1)!= packet)
		{
			vector<string> tmp;
			tmp.push_back(to_string(lastPacket+1));
			Message Packet1440(1440,MessageType::Reply,tmp,rpc_id1);
			tmp = Packet1440.marshal();
			char* buffer = copyStr(tmp[0]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
			//DPSocket::writeToSocket (char * buffer, int maxBytes ){
			//udpServerSocket.setPeerAddr(hostname,port);
      int toSend = tmp[0].size();
			udpServerSocket.writeToSocket(buffer, toSend);
			return false;
		}
		else
		{
			Log[Index].push_back(Packet1);
			return !lastPacketFlag;
		}
	}
	else
	{
		int packet = getPacketNumber(Packet1, lastPacketFlag);
    // cout << "current Packet: " << packet <<endl;
    // cout << "Is it the last? " << lastPacketFlag << endl;
		if(packet)
		{
			vector<string> tmp;
			tmp.push_back(to_string(0));
			Message Packet1440(1440,MessageType::Reply,tmp,rpc_id1);
			tmp = Packet1440.marshal();
      char* buffer = copyStr(tmp[0]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());

		//	udpServerSocket.setPeerAddr(hostname,port);
      int toSend = tmp[0].size();
			udpServerSocket.writeToSocket(buffer, toSend);
			return false;
		}
		else
		{
			Log[Index].push_back(Packet1);
			targetLog[Index] = (targetAddr);
			return !lastPacketFlag;
		}
	}
}

/////private methods defention////////
Message Server::getRequest(){
	string marshalled_base64;
	int maxBytes = SIZE; //to be changed

	while(udpServerSocket.readSocketWithBlock(marshalled_base64,maxBytes)==0){
		// cout << "Recieved this: " <<  marshalled_base64 << endl;
    // cout << "Of Size: " << marshalled_base64.size() << endl;
    // cout << "operation: " << (UnShrinkInt(marshalled_base64.substr(4,4))&0x7fffffff) << endl;
		// //tb2a e3ml thread hna for recieving packets from different resources;


		if (matchPackets(marshalled_base64))
		{
      cout << "I'm forming a message\n";
			int rpc_id1 = UnShrinkInt(marshalled_base64.substr(0,4));
			string hostname;
			int port;
			udpServerSocket.getPeerAddr(hostname, port);
			pair<pair<string, int>, int> Index = make_pair(make_pair(hostname,port),rpc_id1);		// you can't use sockaddr_in because it doesn't have a less than operator defined so no map; instead use port and hostname to build a unique map of pair<pair<int,int>, int>, vector<string>

      vector<string> PhantomMessage;
      PhantomMessage.push_back("g");
      Message Packet1440P(1440,MessageType::Reply,PhantomMessage,rpc_id1);
      Packet1440P.setArgNum(0);
      PhantomMessage = Packet1440P.marshal();
      // cout << "phantom size: "<<PhantomMessage[0].size() << endl;
      //char* buffer = strcpy((char*)malloc(PhantomMessage[0].length()+1),PhantomMessage[0].c_str());
      char* buffer = copyStr(PhantomMessage[0]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());

      //udpServerSocket.setPeerAddr(hostname,port);

      int toSend = PhantomMessage[0].size();
      udpServerSocket.writeToSocket(buffer, toSend);

      Message request_msg(Log[Index]);
			//request_msg.setPeerData(make_pair(hostname,port));
			request_msg.setPeerAddr(targetLog[Index]);
			Log.erase(Index);
			targetLog.erase(Index);
			if(request_msg.getMessageType() == MessageType::Request)
			{
				cout<<"SERVER RECIEVED A REQUEST";
				return request_msg;	//tb2a eft7 thread hna
			}
			else
			{
				cout<<"ERROR : SERVER RECIEVED A REPLY";
				request_msg.setOperation(-10);
				return request_msg;
			}
		}
	}

vector<string> dummy;
Message DummyMsg(-10,Reply,dummy,-10);
return DummyMsg;

}

Message Server::doOperation(Message requested){
	// printf("is it assignment problem?");
	// image x ("def.jpg", args[0], "amr");
	// string res = x.viewImage(args[1]);
	cout << "I'm doing opp:\n";
	vector<string> aho = requested.getMessage();
	for(int i =0; i < aho.size(); i++)
		cout << aho[i] << endl;
	cout << endl;
	vector<string> rep;
	// rep.push_back(res);
	// //Message y(0, Reply, "a7eh", 4, 0);


  //do operation logic
  rep.push_back("h g g");
	Message Z(100, MessageType::Reply, rep, 10);
  Z.setPeerAddr(requested.getPeerAddr());   //to know who to send to;
	return Z;
}

void Server::sendReply (Message  _message){

		int maxBytes = _message.getMessageSize();
		vector<string> str = (_message.marshal());
    // cout << "To be sent: " << str[0].size() << endl;
    string rMessage;
		for(int i =0; i < str.size(); i++)
		{
			//char* buffer = strcpy((char*)malloc(str[i].length()+1),str[i].c_str());
      char* buffer = copyStr(str[i]);//= strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());

      //pair<string, int> tmpAddr = _message.getPeerData();
      udpServerSocket.setPeerAddr(_message.getPeerAddr());
      maxBytes = str[i].size();

      udpServerSocket.writeToSocket(buffer,maxBytes);
			if(i != str.size()-1)
			{
				if(udpServerSocket.readFromSocketWithTimeout(rMessage,maxBytes, 0, 3) == 0)	//something is recieved;
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
			else if(udpServerSocket.readFromSocketWithTimeout(rMessage,maxBytes, 3, 0) == 0)	//something is recieved;
			{
        cout << "Waiting for the confirmation message\n";
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
        // cout << "X.operation: " << X.getOperation() <<endl;
			}
			else{
				i = -1;
			}
		}


}





/////public methods defention////////

Server::Server(char * _listen_hostname, int _listen_port){

	reqID = 0;
	if(udpServerSocket.initializeServer(_listen_hostname,_listen_port)){

		cout<<"A SERVER IS INiTILIZED"<<endl;
		udpServerSocket.enable();
  }

	//	sendReply(getRequest());
	else
	{
		cout<<"ERROR:: Server cannot be intialized"<<endl;
		udpServerSocket.disable();
	}
}



//should be blocking
void Server::serveRequest(){
	if(udpServerSocket.isEnabled())
	{
		//listen(udpServerSocket.getSocketHandler(),5);


		Message mp = getRequest();



		cout << "I got a request\n";
		if(mp.getMessageType()==MessageType::Request)//0 for request 1 for reply
		{
			printf("h3ml 7aga\n");
			Message np = doOperation(mp);
			if(np.getMessageType()==MessageType::Reply)
			{
				printf("Reply is being sent\n");
				sendReply(np);
			}
			else{
				printf("You didn't prepare a reply\n");
			}
		}
	}
	else
	{
		cout<<"SERVER Doesn't accept replies"<<endl;
	}

}
Server::~Server(){}
