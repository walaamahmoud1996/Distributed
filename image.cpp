#include "image.h"

image::image(string def, string inputFile, string username){
  owner = username;
  fileName = inputFile;
  defaultImageFile = def;

  ifstream fin(fileName.c_str(), ios::binary);
  ostringstream ostrm;
  ostrm << fin.rdbuf();
  imageData = (ostrm.str());

  ifstream fin1(defaultImageFile.c_str(), ios::binary);
  ostringstream ostrm1;
  ostrm1 << fin1.rdbuf();
  defaultImage = (ostrm1.str());

  userViews["ahmed"] = 3;

  hideImage();

}

void image::hideImage(){
  //stegnography code here
}

int image::getNumberOfViews(string username){
  return userViews[username];
}

void image::setNumberOfViews(string username, int views){
    userViews[username] = views;
}

string image::viewImage(string username){
  ofstream fout("output.jpg", ios::binary);
  if (userViews[username] <= 0) {
    fout << defaultImage;
  }
  else{
    fout << imageData;
    userViews[username]--;
  }
  return "output.jpg";
}
