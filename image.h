#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>

using namespace std;

class image{
private:
  string defaultImageFile;
  string defaultImage;
  string fileName;
  string imageData;
  string owner;
  string hiddenImage;
  map <string, int> userViews;

  void hideImage();

public:
  image(string def, string inputFile, string username);

  // Owner Side Functions
  int getNumberOfViews(string username);
  void setNumberOfViews(string username, int views);

  string printImage();
  // User Side Functions

  string viewImage(string username);


};

#endif
