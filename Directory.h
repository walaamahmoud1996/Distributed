#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <map>
#include <vector>
#include <Magick++.h>
using namespace Magick;

class Directory
{

private:
	Server D_Server;
	struct image{
		Image img;
		int imageAddr;
	};
	map<char*,char*> DataBase;
	map<char*,vector<Image>> User_Image;
	map<char*,char*>::iterator it_DB;

	map<char*,vector<image>>::iterator it_UI;

public:


	Directory();
	bool SignUp(char* UserName,char* PassWord);

	vector<Image> Login(char*UserName,char* PassWord);


	~Directory();

}

#endif
