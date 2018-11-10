#include "servantImage.h"
//owener side function
servantImage::servantImage(string _image_name, string _actual_image, string _cover_image, string username){

	image_name = _image_name.substr(_image_name.find('!')+1);
	owner = _image_name.substr(0,_image_name.find('!'));
	user_name = username;
	cover_image = _cover_image;
	actual_image = _actual_image;
	convert_to_jpeg(cover_image,actual_image);
	decode(cover_image);
	decode(image_name);

	remove(image_name.c_str());

	ifstream fin( user_name + image_name.substr(0,image_name.find('.')) + ".txt");
	string tmp;
	fin >> user_name;
	fin >> tmp;
	fin.close();
	remove((user_name + image_name.substr(0,image_name.find('.')) + ".txt").c_str());
	numberOfViews = stoi(tmp);
}

bool servantImage::unHideImage()		// make it return a qpix map, then delete the image;
{
	if(numberOfViews)
	{
		convert_to_jpeg(cover_image,actual_image);
		decode(cover_image);
		numberOfViews--;
		//remove(image_name);
		return true;	//return image_name
	}
	else
		return false;	//return cover_image;
}


int servantImage::getNumberOfViews()
{
	return numberOfViews;
}

void servantImage::setNumberOfViews(int views)
{
	numberOfViews = views;
}
