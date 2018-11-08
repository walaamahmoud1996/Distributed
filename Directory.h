#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <map>
#include <vector>
#include <fstream>
#include "Image.h"
#include <string>
//#include <Magick++.h>
//using namespace Magick;
using namespace std;
enum operations={login,take_owner_images,send_images,register_requests};
class Directory
{

private:
	ifstream fin;
	ofstream fout;
	Server D_Server;
	struct image{
		string img;
		string owner_name;
		string image_id;
	};

	map<string,string> DataBase;
	map<string,vector<image>> User_Image;
	map<string,string>::iterator it_DB;

	map<string,vector<image>>::iterator it_UI;

public:


	Directory();
	bool SignUp(string UserName,string PassWord);

	bool Login(string UserName,string PassWord);

	void Take_Owner_Images(vector<string>);


	~Directory();

}

#endif
