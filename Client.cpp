#include "Client.h"

Client::Client(char * _hostname, int _port)
{
	rpc_id=0;
	hostname = _hostname;
	send_port = _port;

	if(udpSocket.initializeClient(_hostname,_port)){
		cout <<"Client in intialized\n";
		udpSocket.enable();
	}
	else
		cout<<"Failed To intialize a Client\n";



}
Client::Client(){

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
void Client::Upload_Image(string image_name){

	Image newImage(image_name+".jpeg",image_name+".txt");

}

void Client::Login(string user_name,string password){
	vector<string> login_p;//parameters
	vector<string> login_r;//reply

	login_p.push_back(user_name);
	login_p.push_back(password);
	rpc_id++;


	Message login_message(int(login),Request,login_p,rpc_id);

	Message login_reply = execute(login_message);

	if(login_reply.getMessageType() == Reply){

		login_r = login_reply.getMessage();
		if(login_r[0]=="true"){

			cout<<"YOU ARE LOGGED IN"<<endl;
			this->username = user_name;
			this->password = password;
			this->Client_Token = login_r[1];
			//this->Give_me_images();
		}
		else
		{
			cout<<"RELOGIN";
		}
	}
	
	

}
void Client::Ping(){

	vector<string> ping_p;
	ping_p.push_back(this->Client_Token);
	ping_p.push_back(this->ip_address);
	ping_p.push_back(to_string())
	rpc_id++;
	Message ping_request(int(ping),Request,ping_p,rpc_id);

	Message ping_reply = execute(ping_request);
	vector<string>images_lables = ping_reply.getMessage();

	images_to_see.insert(images_to_see.end(),images_lables.begin(),images_lables.end())

}
void Client::Take_my_recources(string image_name){

	Image myimg(image_name+".jpeg",image_name+".txt");
	string image = myimg.Get_Actual_Image();
	vector<string> take_recource_p;
	vector<string> take_recource_r;

	take_recource_p.push_back(this->username);

	take_recource_p.push_back(image_name);
	take_recource_p.push_back(image);

	rpc_id++;
	Message take_recource(int(Take_my_recource),Request,take_recource_p,rpc_id);

	Message take_recource_reply = execute(take_recource);

	if(take_recource_reply.getMessageType()==Reply){

		take_recource_r = take_recource_reply.getMessage();

		if(take_recource_r[0]=="true"){

			cout<<"IMAGE AT DIRECTORY NOW";
		}
		else 
		{
			cout<<"IMGAE IS NOT THERE ";
		}
	}

}

void Client::Give_me_images(){

	vector<string> Images_to_see;

	vector<string> give_me_p;
	give_me_p.push_back(this->username);

	rpc_id++;
	Message give_me_request(int(give_me_images),Request,give_me_p,rpc_id);

	Message give_me_reply = execute(give_me_request);


	if(give_me_reply.getMessageType()==Reply){

		Images_to_see = give_me_reply.getMessage();

		for(int i=0;i<Images_to_see.size();i+=2)
		{	
			
			name_to_image[Images_to_see[i]] = Images_to_see[i+1];

			Image cover_img(Images_to_see[i],Images_to_see[i+1],0);
			Image actual_img(Images_to_see[i],"",1);

			ProcessText(Images_to_see[i]);


		}




	}
}
void Client::ProcessText(string text_name){

	string file = text_name+"txt";
	ifstream image_text(file.c_str(),ios::binary);


 	string user;
 	string qouta;

 	while(!image_text.eof())
 	{
 		image_text>>user;
 		image_text>>qouta;
 		if(user==username){
 			image_to_qouta[text_name]=stoi(qouta);
 			break;
 		}
 	}

 	image_text.close();



}
bool Client::Is_Online(string username){
}
void Client::Ask_for_qouta(string owner_name,string image_name){
		vector<string> qouta_p;
		qouta_p.push_back(this->username);
		qouta_p.push_back(image_name);
		rpc_id++;
		vector<string> qouta_r;
	if(Is_Online(owner_name)){
		udpSocket.setPeerAddr(owner_address.first,owner_address.second);
		
		Message qouta_request(int(ask_for_qouta),Request,qouta_p,rpc_id);
		qouta_request.setPeerData(owner_address);
		Message qouta_reply = execute(qouta_request);
		qouta_r = qouta_reply.getMessage();
		if(qouta_r[0]=="true"){image_to_qouta[image_name]=stoi(qouta_r[1]);}
		else{cout<<"OWNER REFUSED TO GIVE YOU QOUTA";}


	}
	else{
		Message register_qouta_request(int(ask_for_qouta),Request,qouta_p,rpc_id);
		Message register_qouta_reply = execute(register_qouta_request);
		cout<<"Request Sent"<<endl;
	}



}




void Client::View_Image(string image_name){

	if(image_to_qouta[image_name]>0){
		image_to_qouta[image_name]--;
		//qt function call to show image
	}
	else
	{
		cout<<"YOU HAVE NO QOUTA"<<endl;
	}
}
Client::~Client(){}