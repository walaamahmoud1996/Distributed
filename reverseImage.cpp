#include"servantImage.h"
using namespace std;


int main()
{
  string image_name = "amr!index.jpeg";
  cout << "getting image\n";
  ifstream fin("testImage.txt", ios::binary);
  ostringstream ostrm;
  ostrm << fin.rdbuf();
  string imageData = (ostrm.str());
  fin.close();
  cout << "creating servant image\n";
  servantImage X(image_name,imageData,"index3.jpg", "ahmed");
  cout << "unhiding image\n";
  while(X.getNumberOfViews())
  {
  X.unHideImage();

  cout << X.getNumberOfViews() << endl;
}


  return 0;
}
