#include "../source/include/UART.hpp"

int main(void){
	UART sendPort(ttyUSB0, 9600, "8N1");
	UART receivePort(ttyUSB1, 9600, "8N1");

	sendPort.connect();
	receivePort.connect();

	sendPort.data_write((uint8_t*) "Test", 4);
	std::cout << "Send string: Test" << std::endl;

	usleep(1000000);

	std::cout << "Received string: " << receivePort.data_read() << std::endl;
	
	sendPort.disconnect();
	receivePort.disconnect();
	return 0;
}