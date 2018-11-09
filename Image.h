#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <string>


using namespace std;


class Image{
private:
  
  void encode(string image_name,string text_name);
  void decode(string image_name);
  string convert_to_string(string image_name);
  void convert_to_jpeg(string image_name,string image_as_string);
  void convert_to_jpeg(string image_as_string);

  //string convert_to_text(string image_as_string);
  string actual_image;
  string cover_image;



public:
    Image(string image_name,string text_name);//owener side function
    //Image(string image_as_string);//directory side function
    //Image(string owener,string Image_id,string cover_as_string);//viewer side function
    Image(string,string,int);
    string Get_Actual_Image();
    string Get_Cover_Image();



};

#endif
