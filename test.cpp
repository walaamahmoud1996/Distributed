#include <iostream>

using namespace std;


class A{
protected:
int a;
private:
	int b;


public:
	void hi(){
		cout<<"hi";
	}
};

class B: public A{


private:
	int a;

protected:
int b;



public:

	

};


int main(){

	B b;

	b.hi();
	return 0;
}