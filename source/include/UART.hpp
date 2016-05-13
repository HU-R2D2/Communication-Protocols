#ifndef _UART_HPP
#define _UART_HPP

#include <queue>
#include "TransportProtocol.hpp"
#include "../../../../deps/serial-master/include/serial/serial.h"

class UART : public TransportProtocol{

public:
	UART(int com, int baud = 9600, int bytesize = 8, int paritytype = 0, double stopbits = 1, int flow  = 0);
	~UART();

	void data_write(uint8_t* data);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

private:
	int comport;
	uint32_t baudrate;
	int databitcount;
	int parity;
	double stopbitcount;
	int flowcontrol;

	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;
};

#endif