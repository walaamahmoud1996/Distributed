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

/*
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"

/*
#include <cv.h>
#include <highgui.h>
*/
using namespace std;
//using namespace cv;

class image{
private:
  string defaultImageFile;
  string defaultImage;
  string fileName;
  string imageData;
  string owner;
  string user_image;
  string imageID;
  map <pair<string,string>, int> userViews;
    map <pair<string,string>, int>::iterator it;


  void hideImage();
  void encode(string,string);
  void decode();
  bool isBitSet(char ch, int pos);


public:
  image(string image_path, string user_qouta_path);
  image(string encoded_image);

  // Owner Side Functions
  int getNumberOfViews(string username,string imageID);
  void setNumberOfViews(string username,string imageID, int views);


  // User Side Functions

  string viewImage(string username,string imageID);


};

#endif
