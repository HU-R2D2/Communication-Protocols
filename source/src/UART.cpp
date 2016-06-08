#include "../include/UART.hpp"

UART::UART(int com, uint32_t baud, int bytesize, int paritytype, double stopbits, int flow) :
comport(com),
baudrate(baud),
databitcount(bytesize),
parity(paritytype),
stopbitcount(stopbits),
flowcontrol(flow)
{
	serial::stopbits_t stopbittype = static_cast<serial::stopbits_t>(stopbitcount);
	if(stopbits == 1.5){
		stopbittype = serial::stopbits_t::stopbits_one_point_five;
	}
	serial::Serial serialconnection(
		"/dev/ttyUSB1",
		baudrate, 
		serial::Timeout::simpleTimeout(serial::Timeout::max()), 
		static_cast<serial::bytesize_t>(databitcount), 
		static_cast<serial::parity_t>(parity), 
		stopbittype, 
		static_cast<serial::flowcontrol_t>(flowcontrol)
	);
}

void UART::data_write(uint8_t* data){
	for(int i = 0; i < (sizeof(data) / sizeof(uint8_t)); i++){
		send_buffer.push(data[i]);	
	}
}

void UART::data_write(std::string data){
	for(int i = 0; i < (sizeof(data)/sizeof(std::string)); i++){
		send_buffer.push(data[i]);
	}
}

uint8_t* UART::data_read(){
	uint8_t data[receive_buffer.size()];
	for(int i = 0; i < receive_buffer.size(); i++){
		data[i] = receive_buffer.front();
		receive_buffer.pop();
	}
	return data;
}

void UART::connect(){
	serialconnection.open();
}

void UART::disconnect(){
	serialconnection.close();
}

void UART::flush(){
	std::queue<uint8_t> empty;
   	std::swap(send_buffer, empty);
   	std::swap(receive_buffer, empty);
   	serialconnection.flush();
}

bool UART::is_open(){
	return serialconnection.isOpen();
}

void UART::run(){
	while(1){
		if(!send_buffer.empty()){
			uint8_t tempSendBuffer[send_buffer.size()];
			for(int i = 0; i < (sizeof(tempSendBuffer) / sizeof(uint8_t)); i++){
				tempSendBuffer[i] = send_buffer.front();
				send_buffer.pop();
			}
			serialconnection.write(tempSendBuffer, send_buffer.size());
			send_buffer.pop();

		}
		/*if(read_size != 0){
			uint8_t* tempReadBuffer[read_size];
			serialconnection.read(tempReadBuffer, read_size);
			for(int j = 0; j < (sizeof(tempReadBuffer) / sizeof(uint8_t)); j++){
				receive_buffer.push(tempReadBuffer[j]);
			}
			read_size = 0;
		}*/
	}
}

void UART::setReadSize(size_t size){
	read_size = size;
}

bool UART::getPort(){
	return serialconnection.isOpen();
}

int main(void){
	UART mySendUart(3);
	mySendUart.connect();
	while(1){
	}
	return 0;
}
