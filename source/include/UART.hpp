#ifndef _UART_HPP
#define _UART_HPP

#include <queue>
#include <iostream>
#include <thread>
#include <unistd.h>
#include "TransportProtocol.hpp"
#include "comport_defines.hpp"
#include "rs232.h"

class UART : public TransportProtocol, public std::thread{

public:
	UART(int comport_nr, int baudrate, const char* mode);

	void data_write(uint8_t* data, int numberOfBytes);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

	void run();
std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;
private:
	int comport;
	int baud;
	const char* mode;

	
};

#endif
