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
	char* ip = copyStr("127.0.0.1");
	Client c(ip,3000);

	c.Take_my_recources("index.jpeg");

	return 0;
}