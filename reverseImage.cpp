#include"servantImage.h"
using namespace std;


int main()
{
  string image_name = "index.jpeg";
  cout << "getting image\n";
  ifstream fin("testImage.txt", ios::binary);
  ostringstream ostrm;
  ostrm << fin.rdbuf();
  string imageData = (ostrm.str());
  fin.close();
  cout << "creating servant image\n";
  servantImage X(image_name,imageData,"ahmed");
  cout << "unhiding image\n";
  X.unHideImage();

  cout << X.getNumberOfViews() << endl;



  return 0;
}
