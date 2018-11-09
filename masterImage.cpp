#include "masterImage.h"
//owener side function
masterImage::masterImage(string _image_name, string owner_name){

	image_name = _image_name;
	owner = owner_name;
	userDirFile = owner + " " + image_name.substr(0,image_name.find('.'))+".txt";
	if(existFile(userDirFile))
	{
		//read data from file
		userViews = readDataToMap(userDirFile);
	}
	else
	{
		ofstream fout(userDirFile);//create an empty file
		fout.close();
	}

}

map<string, int> masterImage::readDataToMap(string fileName)
{
	ifstream fin(fileName);
	map<string,int> extracted;
	while(!fin.eof())
	{
		cout << "reading\n";
		string tmp1;
		int tmp2;
		fin >> tmp1 >> tmp2;
		extracted[tmp1] = tmp2;
	}
	cout <<"read!\n";
	return extracted;
}
/*
Image::Image(string image_as_string){
	convert_to_jpeg(image_as_string);

}*/

pair<string,string> masterImage::Get_Hidden_Image(string user_name){

	if(!userViews.count(user_name))
		setNumberOfViews(user_name, 0);

	string text_input = user_name + " " + to_string(userViews[user_name]);
  string text_name = user_name + image_name.substr(0,image_name.find('.')) + ".txt";
  ofstream fout(text_name);
  fout << text_input;
  fout.close();

	encode(image_name,text_name);
	encode(cover_image,image_name);
	actual_image = convert_to_string(cover_image);

	return make_pair((owner + " " + image_name),actual_image);
}


int masterImage::getNumberOfViews(string username)
{
	return userViews[username];
}


void  masterImage::setNumberOfViews(string username, int views)
{
	userViews[username] = views;
	ofstream fout(userDirFile);
	bool first = true;
	for (auto it:userViews)
	{
		if(!first)
			cout << endl;
		else first = false;
		fout << it.first << " " << it.second;
	}
	fout.close();
}
