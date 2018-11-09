#include "PServer.h"
PServer::PServer(char * _listen_hostname, int _listen_port):Server(_listen_hostname,_listen_port){
	fin.open("DB.txt",ios::binary);
	string user_name;
	string password;
	while(!fin.eof()){
		fin>>user_name;
		fin>>password;
		DataBase[user_name]=password;
	}
}

Message DServer::doOperation(Message requested){

	int operation = requested.getOperation();
	vector<string> request_p = requested.getMessage();
	vector<string> reply_v;

	switch(operation){
		//Directory operations
		case 0:{reply_v=Login(requested);break;}
		case 1:{reply_v=Take_user_recources(requested);break;}
		case 2:{reply_v=Give_viewer_images(requested);break;}
		//peer operations

	}



	//Message Z(0, MessageType::Reply, Reply, 0);
  	//Z.setPeerData(requested.getPeerData());   //to know who to send to;
  	//int rpc_id = requested.getRPCId();
  	Message reply_m(requested.getOperation(),Reply,reply_v,requested.getRPCId());
	reply_m.setPeerAddr(requested.getPeerAddr());
	return reply_m;
}


vector<string> DServer::Login(Message Login_request){
	vector<string> login_p = Login_request.getMessage();
	string user_name = login_p[0];
	string password = login_p[1];
	it_DB = DataBase.find(user_name);
	vector<string>login_r;
	if(it_DB!=DataBase.end())
	{
		login_r.push_back("true");
		string token = generate_token();
		login_r.push_back(token);


		user_token[user_name]=token;
		ping p={"",-1,""};
		token_address[token]=p;

	}
	else{
		login_r.push_back("false");


	}

	return login_r;

}
string DServer::generate_token(){
	static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        string s;
    for (int i = 0; i < 6; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    it_UT = token_address.find(s)
    if(it_UT!=token_address.end()){
    	  return s;

    }
    else return generate_token();

}

void DServer::Ping(Message ping_request){

	vector<string> ping_p= ping_request.getMessage();



}
vector<string> DServer::Take_user_recources(Message take_recource_request){
	vector<string> take_recource_reply;
	vector<string> owner_name_image;//request parameters
	owner_name_image= take_recource_request.getMessage();

	for(int i=0;i<owner_name_image.size();i+=3){

		Image img_recource(owner_name_image[i+1],owner_name_image[i+2],1);
		Process_Text(owner_name_image[i],owner_name_image[i+1],owner_name_image[i+2]);

	}
	take_recource_reply.push_back("true");
	return take_recource_reply;
}
void DServer::Process_Text(string owner_name,string text_name,string image_as_string){
	fin.open((text_name+".txt").c_str(),ios::binary);
	string viewer_name;
	string viewer_qouta;
	while(!fin.eof()){
		fin>>viewer_name;
		fin>>viewer_qouta;
		Viewer_Image[viewer_name].push_back(owner_name);
		Viewer_Image[viewer_name].push_back(text_name);
		Viewer_Image[viewer_name].push_back(image_as_string);
	}
}
vector<string> DServer::Give_viewer_images(Message  give_image_request){
	vector<string> viewer_name;
	viewer_name = give_image_request.getMessage();




	return Viewer_Image[viewer_name[0]];

}


void DServer::serveRequest(){
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
DServer::~DServer(){

}
