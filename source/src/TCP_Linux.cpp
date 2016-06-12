#include "../include/TCP_Linux.hpp"

TCP_Linux::TCP_Linux(std::string ipNr, std::string portNr):
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
	SocketAddress servaddr(ipNr.c_str(), portNr.c_str());
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
	std::string s = "isOpen?";
	sock.send( s.data(), s.size() ); 	
	return true;
	//void CommunicatingSocket::send(const void *buffer, int bufferLen)
}

void TCP_Linux::sendMessage(){
	if(!send_buffer.empty()){
		char* buffer = new char[500];
		sock.send(buffer, buffer.size());
	}

}

void TCP_Linux::receiveMessage(){
	//temp for testing
	char* buffer = new char[500];
	if(( sock.recvFully(buffer, 2) ) != 1){
		buffer[len+1] = '\0';
	}
	std::cout << "fout" << std::endl;
}

void TCP_Linux::run(){

}