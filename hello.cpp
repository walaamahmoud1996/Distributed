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

  Message y(1, Request, x, x[0].size()+x[1].size(), 0);

  string f = y.marshal();
  cout << f << endl;

  Message t(f);




  //image hello ("def.jpg", "hi.jpg", "amr");
  //cout << hello.getNumberOfViews("ahmed");
  //cout << hello.getNumberOfViews("mirco");

  //hello.viewImage("mirco");

  return 0;


}
