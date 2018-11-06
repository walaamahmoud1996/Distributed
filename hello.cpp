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

  x.push_back("hello_world");
  x.push_back("hello");

  Message y(14, Request, x, 12);
  vector<string> amada = y.getMessage();
  for(int i = 0; i < amada.size(); i++)
    cout << amada[i] << endl;
  cout << "+++++++++++++++++\n";
  std::vector<string>  f = y.marshal();
  for(int i = 0; i < f.size(); i++)
    cout << f[i] << endl;
  cout << "++++++++++++++++\n";
  Message t(f);
  vector<string> hamada = t.getMessage();
  for(int i = 0; i < hamada.size(); i++)
    cout << hamada[i] << endl;


/*
  image hello ("index1.png", "index1.png", "amr");
  cout << hello.getNumberOfViews("ahmed")<<endl;
  cout << hello.getNumberOfViews("mirco")<<endl;

  cout<< hello.viewImage("ahmed") << endl;
  string g = hello.printImage();
  x.clear();
  x.push_back(g);
  Message z(1, Request, x ,0);
  string n = z.marshal();
  cout << n << endl;

*/

  return 0;


}
