#include "Image.h"
//owener side function
Image::Image(string image_name,string text_name){

	encode(image_name,text_name);
	actual_image = convert_to_string(image_name);

}
//viewer side constructor
Image::Image(string owner,string image_id,string cover_as_string){

	convert_to_jpeg(owner,cover_as_string);
	//convert_to_jpeg("cover.jpeg",cover_as_string);

	decode("cover"+owner+image_id+".jpeg");

	string image_as_string = convert_to_string(owner+image_id+".txt");

	convert_to_jpeg(owner+image_id+".jpeg",image_as_string);
	decode(owner+image_id+"jpeg");
	

}
Image::Image(string image_as_string){
	convert_to_jpeg(image_as_string);
	decode("owner.jpeg");
	
}
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


string Image::Get_Actual_Image(){
	return actual_image;
}
string Image::Get_Cover_Image(){
	return cover_image;
}