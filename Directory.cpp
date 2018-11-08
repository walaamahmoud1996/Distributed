#include "Directory.h"


Directory::Directory(){

}

bool Direcotory::SignUp(string UserName,string  PassWord){


  it_DB = DataBase.find(UserName);
	if(it_DB != DataBase.end())
	{
		cout << "USERNAME ALREADY IN USE\n";
		return false;
	}
	else
	{
		DataBase[UserName] = PassWord;
		cout << "WELCOME TO SERVICE\n";
    fout << UserName << " : " << DataBase[Username] << endl;
		return true;
	}

}

bool Directory::Login(string  UserName,string PassWord){

	it_UI = UserImage.find(UserName);

	if(it_UI != UserImage.end())
	{
		cout<<"YOU ARE NOT A USER\n";
		return false;
	}
	else
	{
		DataBase[UserName]= PassWord;
		cout<<"WELCOME TO SERVICE\n";

		return true;
	}


}

void Directory::Take_Owner_Images(string owner_name,vector<string> images_ids,vector<string> owner_images){

	for(int i=0;i<owner_images.size();i++){
		Image(owner_images[i]);
		Process_Text(images_ids[i],owner_images[i]);


	}

}

void Directory::Process_Text(string text_name,string owner_image){

	ifstream qouta_text(text_name.c_str(),ios::binary);

	string viewer_name;
	string qouta;
	while(!qouta_text.eof()){
		qouta_text>>viewer_name;
		qouta_text>>qouta;
		User_Image[viewer_name].push_back(owner_image);
	}

}
~Directory::Directory(){

}

