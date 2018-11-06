#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <map>
#include <vector>
#include <fstream>
//#include <Magick++.h>
//using namespace Magick;
using namespace std;

class Directory
{

private:
	ifstream fin;
	ofstream fout;
	Server D_Server;
	struct image{
		Image img;
		int imageAddr;
	};
	map<char*,char*> DataBase;
	map<char*,vector<image>> User_Image;
	map<char*,char*>::iterator it_DB;

	map<char*,vector<image>>::iterator it_UI;

public:


	Directory();
	bool SignUp(char* UserName,char* PassWord);

	vector<Image> Login(char*UserName,char* PassWord);


	~Directory();

}

#endif
