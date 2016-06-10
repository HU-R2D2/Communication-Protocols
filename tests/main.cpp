#include "../source/include/UART.hpp"

int main(void){
	UART sendPort(ttyUSB2, 9600, "8N1");
	UART receivePort(ttyUSB3, 9600, "8N1");
	std::thread t(&UART::run, &sendPort);
	std::thread k(&UART::run, &receivePort);
	sendPort.connect();
	receivePort.connect();
	uint8_t* test = (uint8_t*) "Test";
	sendPort.data_write(test, 4);
	usleep(1000000);
	std::cout << "blabla" << receivePort.data_read() << std::endl;
	sendPort.disconnect();
	receivePort.disconnect();
	return 0;
}