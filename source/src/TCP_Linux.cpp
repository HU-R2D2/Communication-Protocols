#include "../include/TCP_Linux.hpp"

TCP_Linux::TCP_Linux(std::string ipNr, std::string portNr):
	ipNr(ipNr),
	portNr(portNr)
{
}

TCP_Linux::~TCP_Linux(){
	runningThread.join();
}

void TCP_Linux::connect(){
	SocketAddress servaddr(ipNr.c_str(), portNr.c_str());
	sock.connect(servaddr);
	is_running = true;
	open = true;
	runningThread = std::thread(&TCP_Linux::run, this);
	std::cout << "connected!" << std::endl;
}

void TCP_Linux::disconnect(){
	std::cout << "disc" << std::endl;
	is_running = false;
	sock.close();
}

void TCP_Linux::flush(){
	std::queue<uint8_t> empty;
	std::swap(send_buffer, empty);
	std::swap(receive_buffer, empty);
}

bool TCP_Linux::is_open(){

	return open;
}

void TCP_Linux::data_write(uint8_t* data, int numberOfBytes){
	for (unsigned int i = 0; i < numberOfBytes; i++) {
		send_buffer.push(data[i]);
	}
	std::cout << "\ndata_write done! \n" << std::endl;
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

void TCP_Linux::send_message(){
	if(!send_buffer.empty()){
		std::cout << "buffer is not empty" <<std::endl;
		int s = send_buffer.size();
		char* data = new char[500];
		for (int i = 0; i < s; i++) {
			data[i] = send_buffer.front();
			send_buffer.pop();
		}
		try{
			//std::cout << data << std::endl;
			sock.send(data, s);
		}
		catch (SocketException &e) { 
			std::cout << "ERRROROROOROR" << std::endl;
			std::cerr << e.what() << std::endl; 
		}
	}
}

void TCP_Linux::send_message(const char * message){
	sock.send( message, strlen(message) );
	std::cout << "message send " << std::endl;
}

void TCP_Linux::set_receive_timeout(int usec){
	struct timeval timeout;      
	timeout.tv_sec = 0;
	timeout.tv_usec = usec;
	//int s = sock.getSocketDesc();
	if (setsockopt (sock.getSocketDesc(), SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
		sizeof(timeout)) < 0){
			std::cout << ("setsockopt failed\n") << std::endl;
		}
}

void TCP_Linux::receive_message(){
	char* tempReceiveBuf = (char*)malloc(4096);
	iResult = sock.recvFully(tempReceiveBuf, 400);	
	if(iResult > 0 ){
		for (int i = 0; i < iResult; i++) {
			receive_buffer.push(tempReceiveBuf[i]);
		}
		for(auto &TransportListener : transportListeners){
			TransportListener->data_received( (uint8_t *)&tempReceiveBuf);
		}
	}
	else if(iResult == 0){
		std::cout << "Error: didn't receive anything" << std::endl;
	}
}

void TCP_Linux::run(){
	while(true){
		if(is_open()){
			std::cout << "running" << std::endl;
			send_message();
			receive_message();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}

void TCP_Linux::set_listener(TransportListener * t){
	transportListeners.push_back(t);
}

void TCP_Linux::remove_listener(TransportListener * t){
	transportListeners.erase(std::remove(transportListeners.begin(), transportListeners.end(), t), transportListeners.end());
}

