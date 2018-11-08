#include "Server.h"
using namespace std;


int Server::UnShrinkInt(string tmp)
{
  int x = 0;
  for(int i =0; i < 4;i++)
  {
    int tmpx = tmp[i] &0xff;
    x |= (tmpx<<(i*8));
  }
  return x;

}

int Server::getPacketNumber(string message, bool& end)
{
	int tmp = UnShrinkInt(message.substr(12,4));
  end = (tmp >> 31);
  tmp &= 0x7fffffff;
	return tmp;
}



bool Server::matchPackets(string Packet1)
{
	int rpc_id1 = UnShrinkInt(Packet1.substr(0,4));
	string hostname;
	int port;
	udpServerSocket.getPeerAddr(hostname, port);
	pair<pair<string, int>, int> Index = make_pair(make_pair(hostname,port),rpc_id1);		// you can't use sockaddr_in because it doesn't have a less than operator defined so no map; instead use port and hostname to build a unique map of pair<pair<int,int>, int>, vector<string>
	bool lastPacketFlag = false;
	vector<string >tmp;
//	Log[ make_pair(Addr,rpc_id1)] = tmp;
	if(Log.count(Index))
	{
		string tmp = Log[Index][Log[Index].end()-Log[Index].begin() + 1];
		int lastPacket = getPacketNumber(tmp, lastPacketFlag);
		int packet = getPacketNumber(Packet1, lastPacketFlag);
		if( (lastPacket+1)!= packet)
		{
			vector<string> tmp;
			tmp.push_back(to_string(lastPacket+1));
			Message Packet1440(1440,MessageType::Reply,tmp,rpc_id1);
			tmp = Packet1440.marshal();
			char* buffer = strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
			//DPSocket::writeToSocket (char * buffer, int maxBytes ){
			udpServerSocket.setPeerAddr(hostname,port);
			udpServerSocket.writeToSocket(buffer, SIZE);
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
		if(packet)
		{
			vector<string> tmp;
			tmp.push_back(to_string(0));
			Message Packet1440(1440,MessageType::Reply,tmp,rpc_id1);
			tmp = Packet1440.marshal();
			char* buffer = strcpy((char*)malloc(tmp[0].length()+1),tmp[0].c_str());
			udpServerSocket.setPeerAddr(hostname,port);
			udpServerSocket.writeToSocket(buffer, SIZE);
			return false;
		}
		else
		{
			Log[Index].push_back(Packet1);
			return !lastPacketFlag;
		}
	}
}

/////private methods defention////////
Message Server::getRequest(){
	string marshalled_base64;
	int maxBytes = SIZE; //to be changed

	while(udpServerSocket.readSocketWithBlock(marshalled_base64,maxBytes)>=0){
		cout << marshalled_base64 << endl;
		//tb2a e3ml thread hna for recieving packets from different resources;


		if (matchPackets(marshalled_base64))
		{
			int rpc_id1 = UnShrinkInt(marshalled_base64.substr(0,4));
			string hostname;
			int port;
			udpServerSocket.getPeerAddr(hostname, port);
			pair<pair<string, int>, int> Index = make_pair(make_pair(hostname,port),rpc_id1);		// you can't use sockaddr_in because it doesn't have a less than operator defined so no map; instead use port and hostname to build a unique map of pair<pair<int,int>, int>, vector<string>
			Message request_msg(Log[Index]);
			request_msg.setPeerData(make_pair(hostname,port));
			Log.erase(Index);
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
	vector<string> rep;
	// rep.push_back(res);
	// //Message y(0, Reply, "a7eh", 4, 0);


  //do operation logic

	Message Z(0, MessageType::Reply, rep, 0);
  Z.setPeerData(requested.getPeerData());   //to know who to send to;
	return Z;
}

void Server::sendReply (Message  _message){

		int maxBytes = _message.getMessageSize();
		vector<string> str = (_message.marshal());

    string rMessage;
		for(int i =0; i < str.size(); i++)
		{
			char* buffer = strcpy((char*)malloc(str[i].length()+1),str[i].c_str());

      pair<string, int> tmpAddr = _message.getPeerData();
      udpServerSocket.setPeerAddr(tmpAddr.first, tmpAddr.second);

			if(i != str.size()-1)
			{
				if(udpServerSocket.writeToSocketAndWait(buffer,maxBytes, 0, 3, rMessage) == 0)	//something is recieved;
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
			else if(udpServerSocket.writeToSocketAndWait(buffer,maxBytes, 3 ,0, rMessage) == 0)	//something is recieved;
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
