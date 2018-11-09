#ifndef PSERVER_H
#define PSERVER_H
#include "Server.h"
#include "Message.h"
#include "Image.h"
#include <fstream>
#include <map>
#include <vector>
using namespace std;

class PServer: public Server{
private:



	ifstream fin;
	ofstream fout;


	map<string, map<string,int>> ownedImages;			//each image to (each user to number of views)



	Message doOperation(Message requested);
	vector<string> requestImage(Message);
	vector<string> updateQuota(Message);



public:
	//DServer();
	PServer(char * _listen_hostname, int _listen_port, vector<string> owned);
	void serveRequest();
	~PServer();
};
#endif
