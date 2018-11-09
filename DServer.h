#ifndef DSERVER_H
#define DSERVER_H
#include "Server.h"
#include "Message.h"
#include "Image.h"
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class DServer: public Server{
private:



	ifstream fin;
	ofstream fout;
	
	
	map<string,string> DataBase;
	map<string,vector<string>> Viewer_Image;
	map<string,string>::iterator it_DB;
	map<string,string> user_token;
	map<string,string>::iterator it_UT;

	struct ping{
		string ip,
		int port,
		string timeStamp
	};

	map<string,ping> token_adderss;
	//map<string,vector<image>>::iterator it_UI;


	Message doOperation(Message requested);
	vector<string> Login(Message);
	vector<string> Take_user_recources(Message);
	vector<string> Take_registered_request(Message);
	vector<string> Give_viewer_images(Message);
	void Process_Text(string,string,string);

	string generate_token();
public:
	//DServer();
	DServer(char * _listen_hostname, int _listen_port);
	void serveRequest();	
	~DServer();
};
#endif