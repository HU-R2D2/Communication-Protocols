#include "../include/TCP_Linux.hpp"


TCP_Linux::TCP_Linux(char * ipNr, char * portNr):
	ipNr(ipNr),
	portNr(portNr)
{
}

void TCP_Linux::data_write(uint8_t* data, int numberOfBytes){
	std::cout << "\ndata_write done! \n" << std::endl;
	for (unsigned int i = 0; i < numberOfBytes; i++) {
		send_buffer.push(data[i]);
	}
}

uint8_t* TCP_Linux::data_read(){
	uint8_t * data = new uint8_t[sizeof(receive_buffer)];
	if (!receive_buffer.empty()) {
		for (unsigned int i = 0; sizeof(receive_buffer); i++) {
			data[i] = receive_buffer.front();
			receive_buffer.pop();
		}
	}
	return data;
}

void TCP_Linux::connect(){
	SocketAddress servaddr(ipNr, portNr);
	sock.connect(servaddr);
}

void TCP_Linux::disconnect(){
	sock.close();
}

void TCP_Linux::flush(){
	std::queue<uint8_t> empty;
	std::swap(send_buffer, empty);
	std::swap(receive_buffer, empty);
}

bool TCP_Linux::is_open(){

}

void TCP_Linux::run(){

}