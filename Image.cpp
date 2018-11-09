#include "Image.h"

void Image::encode(string image_name,string text_name){

	string line = "steghide embed -ef ";
    line+=text_name;
    line+=" -cf ";
    line+=image_name;
    line+=" --passphrase 123";
    system(line.c_str());
}

void Image::decode(string image_name){

	string line = "steghide extract -sf ";
	line+= image_name;
	line+= " --passphrase 123";
	system(line.c_str());

}

string Image::convert_to_string(string image_name){


	ifstream input_image(image_name.c_str(),ios::binary);
	ostringstream ostrm;
	ostrm<<input_image.rdbuf();

	return (ostrm.str());


}

void Image::convert_to_jpeg(string image_name,string image_as_string){

	ofstream output_image(image_name.c_str(),std::ofstream::binary);
	output_image<<image_as_string;

}
void Image::convert_to_jpeg(string image_as_string){
	string image_name = "owner.jpeg";
	ofstream output_image(image_name.c_str(),std::ofstream::binary);
	output_image<<image_as_string;

}

void Image::setCoverImage(string _coverImage)
{
	cover_image = _coverImage;
}

string Image::getCoverImage()
{
	return cover_image;
}
