#ifndef MASTERIMAGE_H
#define MASTERIMAGE_H
#include"Image.h"
using namespace std;


class masterImage: public Image{
private:
  map <string, int> userViews;
  string owner;
  string userDirFile;


  map<string, int> readDataToMap(string);


public:
    masterImage(string _image_name,string owner_name);//owener side function
    //Image(string image_as_string);//directory side function
    //Image(string owener,string Image_id,string cover_as_string);//viewer side function

    pair<string,string> Get_Hidden_Image(string);

    int getNumberOfViews(string username);
    void setNumberOfViews(string username, int views);


};

#endif
