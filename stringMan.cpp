#include"stringMan.h"
using namespace std;


char* copyStr(string from1)
{
  char* to1 = new char[from1.size()+1];
  for(int i =0;i< from1.size();i++)
  {
    to1[i] = from1[i];
  }
  to1[from1.size()] = 0;
  return to1;
}

string ShrinkInt(int x)
{
	string returned = "";
	for(int i =0; i < 4; i++)
	{
		char z = x & 0xff;
    cout << z << endl;
		returned.push_back(z);
		x = x>>8;
	}
	return returned;
}

int UnShrinkInt(string tmp)
{
  int x = 0;
  for(int i =0; i < 4;i++)
  {
    int tmpx = tmp[i] &0xff;
    x |= (tmpx<<(i*8));
  }
  return x;

}


bool existFile(string fileName)
{
  const char *name = fileName.c_str();
  struct stat   buffer;
  return (stat (name, &buffer) == 0);
}
