#include "../source/include/TCP_Linux.hpp"

int main(void){
	//TCP_Linux* sock1 = new TCP_Linux("127.0.0.1", "27015");
	TCP_Linux s1("127.0.0.1", "8080");
	s1.connect();
	s1.data_write((uint8_t *)"waila", 5);
	std::this_thread::sleep_for(std::chrono::milliseconds(200000));
	s1.disconnect();
	/*
	usleep(wacht);
	
	std::cout << "sleep1" << std::endl;
	s1.data_write((uint8_t *) "i wrote this", 22);
	usleep(wacht);
	s1.send_message();
	std::cout << "sleep2" << std::endl;
	s1.receive_message();
	usleep(wacht);
	std::cout << "sleep3" << std::endl;
	s1.disconnect();
	std::cout << "disconnected" << std::endl;
	s1.send_message();
	*/
}