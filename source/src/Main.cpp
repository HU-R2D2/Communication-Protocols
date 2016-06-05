#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "../include/TCPSocket.hpp"


int main(){
	std::string a = "127.0.0.1";
	std::string b = "27015";
	
	TCPSocket* tcp1 = new TCPSocket(a, b);
	printf("test");
	return 0;
}