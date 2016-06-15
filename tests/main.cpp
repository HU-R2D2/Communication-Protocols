#include "../source/include/UART.hpp"

int main(void){
	UART sendPort(COM3, 9600, "8N1");
	UART receivePort(COM4, 9600, "8N1");

	sendPort.connect();
	receivePort.connect();

	sendPort.data_write((uint8_t*) "Test", 4);
	std::cout << "Send string: Test" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(400));

	std::cout << "Received string: " << receivePort.data_read() << std::endl;
	
	sendPort.disconnect();
	receivePort.disconnect();
	return 0;
}