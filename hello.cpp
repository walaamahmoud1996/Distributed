#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

#include "image.h"
#include "Message.h"


int main(){

  vector <string> x;

  x.push_back("hello world");
  x.push_back("hello");

  Message y(1, Request, x, 0);

  string f = y.marshal();
  cout << f << endl;

  Message t(f);




  image hello ("index.jpg", "index.jpg", "amr");
  cout << hello.getNumberOfViews("ahmed")<<endl;
  cout << hello.getNumberOfViews("mirco")<<endl;

  cout<< hello.viewImage("ahmed");

  return 0;


}
