#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<map>
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


//   int x = 133899057;
//   string tmp = ShrinkInt(x);
//   int y = UnShrinkInt(tmp);
//   cout << x << " " << tmp <<" " << y;
//
//
// string a = "abcd";
// string b = a.substr(0,3);
// string c = a.substr(3,3);
// cout << a <<" " << b << " " << c <<endl;
//
// cout << a.size() <<" " << b.size() << " " << c.size() <<endl;
//
//
//
// int x = 0b1;
// cout << (x << 8) << endl;

// int cnt = 0;
// for(int i =0;i < 15; i++)
// {
// 	cout << i << endl;
// 	if(i == 5)
// 	{
// 		i = 4;
// 		cnt++;
// 	}
// 	if(cnt == 3) break;
// }



string x = "amr.xcvx";
string y = "sadfa.adfasdfa";
string z = y + " " + x.substr(0,x.find('.'))+".txt";
cout << z<< endl;
ofstream fout(z);
map<string, int> Abs;
Abs["a"] = 3;
Abs["c"] = 12;

for(auto it:Abs)
	fout << it.first << " " << it.second << endl;




fout.close();



  return 0;


}
