#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string>

#include "Client.h"

//#include "Message.h"



using namespace std;
int main(){
	Client c;
	string s= "walaa";
	c.Upload_Image(s);
	


	return 0;
}