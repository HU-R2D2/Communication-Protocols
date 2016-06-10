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
	TCP_Linux(char * ipNr, char * portNr)	;

	void data_write(uint8_t* data, int numberOfBytes);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

	void run();

private:
	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;
	const char * ipNr;
	const char *portNr;
	TCPSocket sock;
};

#endif
