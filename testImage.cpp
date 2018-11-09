#include"masterImage.h"
using namespace std;



int main()
{
  cout << "create the image\n";
  masterImage X ("index.jpeg", "amr");
  cout << "set the cover\n";
  X.setCoverImage("index3.jpg");
  cout << "modify number of views\n";
  X.setNumberOfViews("ahmed", 5);
  cout <<"get the hiddenImage\n";
  pair<string,string> newImage;
  newImage = X.Get_Hidden_Image("ahmed");
  cout << newImage.first<<endl;

  ofstream fout("testImage.txt");
  fout << newImage.second;
  fout.close();
  return 0;
}
