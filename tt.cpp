#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;


string ShrinkInt(int x)
{
	string returned = "";
	for(int i =0; i < 4; i++)
	{
		char z = x & 0xff;
    cout << z<< endl;
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

int main()
{


/*  int x = 133899057;
  string tmp = ShrinkInt(x);
  int y = UnShrinkInt(tmp);
  cout << x << " " << tmp <<" " << y;
*/
/*
string a = "abcd";
string b = a.substr(0,3);
string c = a.substr(3,3);
cout << a <<" " << b << " " << c <<endl;

cout << a.size() <<" " << b.size() << " " << c.size() <<endl;

*/

int x = 0b1;
cout << (x << 8) << endl;

  return 0;


}
