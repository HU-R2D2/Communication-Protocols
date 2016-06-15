#ifndef _TCP_LINUX_HPP
#define _TCP_LINUX_HPP

#include <queue>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include "TransportProtocol.hpp"
#include <algorithm>
#include "../../deps/practicalSocket/PracticalSocket.h"

class TCP_Linux : public TransportProtocol, public std::thread{

public:
	TCP_Linux(){}
	~TCP_Linux();
	TCP_Linux(std::string ipNr, std::string portNr);
	
	void data_write(uint8_t* data, int numberOfBytes);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

	void send_message();
	
	void send_message(const char * message);
	
	void set_receive_timeout(int milisec);
	
	void receive_message();

	void run();

	void set_listener(TransportListener * t);
	
	void remove_listener(TransportListener * t);

private:
	TCPSocket sock;
	std::thread runningThread;

	bool is_running = false;
	const std::string ipNr, portNr;
	int iResult;
};

#endif
