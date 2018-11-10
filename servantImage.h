#ifndef SERVANTIMAGE_H
#define SERVANTIMAGE_H

#include"Image.h"

using namespace std;


class servantImage: public Image{
private:
  string owner;
  string user_name;
  string image_name;
  int numberOfViews;


public:
    servantImage(string, string,string,string);
    bool unHideImage();       //to be changed when we know the requirement for the QT;
    int getNumberOfViews();
    void setNumberOfViews(int views);

};

#endif
