#include "../include/UART.hpp"
#include <unistd.h>

UART::UART(int comport_nr, int baudrate, const char* mode_type):
comport(comport_nr),
baud(baudrate),
mode(mode_type)
{
	RS232_setPortInvalid();
}

UART::~UART(){
	runningThread.join();
}

void UART::data_write(uint8_t* data, int numberOfBytes){
	for(int i = 0; i < numberOfBytes; i++){
		send_buffer.push(data[i]);
	}
}

uint8_t* UART::data_read(){
	uint8_t* tempBuf = (uint8_t*) malloc(receive_buffer.size()*sizeof(uint8_t*));
	int size = receive_buffer.size();
	for(int i = 0; i < size; i++){
		tempBuf[i] = receive_buffer.front();
		receive_buffer.pop();
	}
	return tempBuf;
}

void UART::connect(){
	RS232_OpenComport(comport, baud, mode);
	running = true;
	runningThread = std::thread(&UART::run, this);
}

void UART::disconnect(){
	RS232_CloseComport(comport);
	running = false;
}

void UART::flush(){
	RS232_flushRXTX(comport);
	std::queue<uint8_t> empty;
	std::swap(send_buffer, empty);
	std::swap(receive_buffer, empty);
}

bool UART::is_open(){
	if(RS232_cport(comport) == -1){
		return false;
	}
	else{
		return true;
	}
}

void UART::set_listener(TransportListener * t){
	transportListeners.push_back(t);
}

void UART::remove_listener(TransportListener * t){
	transportListeners.erase(std::remove(transportListeners.begin(), transportListeners.end(), t), transportListeners.end());
}

void UART::run(){
	unsigned char* tempSendBuf;
	unsigned char* tempReceiveBuf = (unsigned char*) malloc(4096);
	int numberOfReadBytes = 0;
	while(running){
		if(is_open()){
			if(send_buffer.size() > 0){
				uint size = send_buffer.size();
				tempSendBuf = (unsigned char*) malloc(size);
				for(uint i = 0; i < size; i++){
					tempSendBuf[i] = send_buffer.front();
					send_buffer.pop();
				}
				RS232_SendBuf(comport, tempSendBuf, size);
			}
			if((numberOfReadBytes = RS232_PollComport(comport, tempReceiveBuf, 4096)) > 0){
				for(int i = 0; i < numberOfReadBytes; i++){
					receive_buffer.push(tempReceiveBuf[i]);
					for(auto &TransportListener : transportListeners){
						TransportListener->data_received(&tempReceiveBuf[i]);
					}
				}
				numberOfReadBytes = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	}
}
