#include<string>
#include<vector>
#include<iostream>
using namespace std;

int main()
{
vector<string> x;
x.push_back("abcd");
x.push_back("edfg");
cout << x[0].size()+x[1].size() <<endl;
cout <<sizeof(x)/float(sizeof(char)) << endl;
cout << sizeof(std::vector<char>) + (sizeof(char) * x.size()) <<endl;
cout << sizeof(x)<< endl;
cout << sizeof(char) << endl;
cout << sizeof(vector<string>) << endl;

return 0;


}
