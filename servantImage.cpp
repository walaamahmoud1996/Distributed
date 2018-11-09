#include "servantImage.h"
//owener side function
servantImage::servantImage(string _image_name, string _actual_image, string username){

	image_name = _image_name.substr(_image_name.find(' '));
	owner = _image_name.substr(0,_image_name.find(' '));
	user_name = username;
	cover_image = "index3.jpg";
	actual_image = _actual_image;
	convert_to_jpeg(cover_image,actual_image);
	decode(cover_image);
	decode(image_name);

	ofstream corrupt(image_name);
		corrupt << "xx\n";
	corrupt.close();

	ifstream fin( user_name + image_name.substr(0,image_name.find('.')) + ".txt");
	string tmp;
	fin >> tmp;
	fin >> tmp;
	numberOfViews = stoi(tmp);
}

void servantImage::unHideImage()
{
	if(numberOfViews)
	{
		convert_to_jpeg(cover_image,actual_image);
		decode(cover_image);
		ifstream fin( user_name + image_name.substr(0,image_name.find('.')) + ".txt");
		string tmp;
		fin >> tmp;
		fin >> tmp;
		numberOfViews--;
	}
}


int servantImage::getNumberOfViews()
{
	return numberOfViews;
}

void servantImage::setNumberOfViews(int views)
{
	numberOfViews = views;
}
