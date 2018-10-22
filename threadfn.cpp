#include <iostream>
#include <thread>

using namespace std;
void threadfn(){

cout<<"inside a thread"<<endl;
}
int main(){
	thread t1(threadfn);
	t1.join();

	return 0;
}