#include "image.h"
/*
image::image(string def, string inputFile, string username){

  /*
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

  std::ofstream outfile ("hidden_msg.txt",std::ofstream::binary);



  outfile<<imageData;

  userViews["ahmed"] = 3;

  hideImage();


}
*/
image::image(string image_path, string user_qouta_path){

  
  encode(image_path,user_qouta_path);
  ifstream input_image(image_path.c_str(),ios::binary);
  ifstream input_qouta(user_qouta_path.c_str(),ios::binary);
  ostringstream ostrm;
  ostrm << input_image.rdbuf();
  user_image = (ostrm.str());
  ofstream output_image("hidden_img.txt",std::ofstream::out);
  output_image<<user_image;
  encode(imageID+".jpg","hidden_img.txt");

}

image::image(string encoded_image){

  

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

string image::viewImage(string username,string imageID){
  ofstream(imageID+"jpg",std::ofstream::binary)
  it = userViews.find(make_pair(username,imageID));
  if (it !=userViews.end()) {
    fout << imageData;
    //cout << imageData;
    userViews[make_pair(username,imageID)]--;
   
    //cout << defaultImage;
  }
  else{
    fout << defaultImage;
    cout<<"YOU DON'T HAVE QOUTA"<<endl;
  }
  return "output.jpg";
}
bool image::isBitSet(char ch, int pos) {
  // 7 6 5 4 3 2 1 0
  ch = ch >> pos;
  if(ch & 1)
    return true;
  return false;
}



void image::encode(string image_name,string text_name){
 
  
    string line = "steghide embed -ef ";
    line+=text_name;
    line+=" -cf ";
    line+=image_name;
    line+=" --passphrase 123";
  system(line.c_str());


  //system("steghide embed -ef DB.txt -cf default.jpg --passphrase 123");

}

void image::decode(){
  system("steghide extract -sf default.jpg --passphrase 123");

}
  /*
  Mat pic = imread("default.jpg");
  if(pic.empty()) {
    cout << "pic Error\n";
    exit(-1);
  }

  // char to work on
  char ch=0;
  // contains information about which bit of char to work on
  int bit_count = 0;

  /*
  To extract the message from the pic, we will iterate through the pixels and extract the LSB of
  the pixel values (RGB) and this way we can get our message.
  */
/*
  for(int row=0; row < pic.rows; row++) {
    for(int col=0; col < pic.cols; col++) {
      for(int color=0; color < 3; color++) {

        // stores the pixel details
        Vec3b pixel = pic.at<Vec3b>(Point(row,col));

        // manipulate char bits according to the LSB of pixel values
        if(isBitSet(pixel.val[color],0))
          ch |= 1;

        // increment bit_count to work on next bit
        bit_count++;

        // bit_count is 8, that means we got our char from the encoded pic
        if(bit_count == 8) {

          // NULL char is encountered
          if(ch == '\0')
            goto OUT;

          bit_count = 0;
          imageData+=ch;
          ch = 0;
        }
        else {
          ch = ch << 1;
        }

      }
    }
  }
  OUT:;


 


}*/