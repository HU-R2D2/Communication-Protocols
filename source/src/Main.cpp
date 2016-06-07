#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "../include/TCPSocket.hpp"


int main(){
	std::string a = "127.0.0.1";
	std::string b = "27015";
	TCPSocket* sock1 = new TCPSocket();
    sock1->t_data_write("holla");
	//TCPSocket* tcp1 = new TCPSocket("127.0.0.1", "27015");
	printf("test");
	return 0;
}