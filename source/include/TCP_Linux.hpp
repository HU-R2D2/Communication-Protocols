#ifndef _TCP_LINUX_HPP
#define _TCP_LINUX_HPP

#include <queue>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "TransportProtocol.hpp"
#include "../../deps/practicalSocket/PracticalSocket.h"

class TCP_Linux : public TransportProtocol, public std::thread{

public:
	TCP_Linux(){}
	TCP_Linux(std::string ipNr, std::string portNr);

	void data_write(uint8_t* data, int numberOfBytes);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

	void sendMessage();
	
	void receiveMessage();

	void run();

	bool set_listener(TransportProtocol * t);
	
	bool remove_listener(TransportProtocol * t);

private:
	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;
	//const char * ipNr;
	//const char *portNr;
	TCPSocket sock;
	const std::string ipNr, portNr;
	
	
};

#endif
