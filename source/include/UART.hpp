#ifndef _UART_HPP
#define _UART_HPP

#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include "TransportProtocol.hpp"
#include "serial/serial.h"

class UART : public TransportProtocol, public std::thread{

public:
	UART(int com, uint32_t baud = 9600, int bytesize = 8, int paritytype = 0, double stopbits = 1, int flow  = 0);

	void data_write(uint8_t* data);

	void data_write(std::string data);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

	void run();

	void setReadSize(size_t size);

	bool getPort();

private:
	int comport;
	uint32_t baudrate;
	int databitcount;
	int parity;
	double stopbitcount;
	int flowcontrol;

	size_t read_size = 0;

	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;

	serial::Serial serialconnection;
};

#endif
