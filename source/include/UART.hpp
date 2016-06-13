#ifndef _UART_HPP
#define _UART_HPP

#include <queue>
#include <iostream>
#include <thread>
#include <algorithm>
#include "TransportProtocol.hpp"
#include "comport_defines.hpp"
#include "rs232.h"


/// A protocol class for UART, wrapper for the RS232 library.
/// \author Thijs Hendrickx
/// \version 1.0
/// \date 13-6-2016
class UART : public TransportProtocol, public std::thread{

public:

	/// Constructor for initialising UART connection.
	/// \param comport_nr The com port which to connect to. 
	/// This is for example COM4 for windows or ttyUSb4 for linux. 
	/// Full list of defines can be found in comport_defines.hpp
	/// \param baudrate The baudrate to use when sending and 
	/// receiving data over the selected com port.
	/// \param mode The settings to use for the connection, 
	/// data bits, parity and stopbits.
	UART(int comport_nr, int baudrate = 9600, const char* mode = "8N1");

	/// Destructor for UART connection.
	~UART();

	/// Method for writing data to the send_buffer queue, 
	/// for it to be send through the com port.
	/// \param data The data to be send
	/// \param numberOfBytes Length of the data in bytes
	void data_write(uint8_t* data, int numberOfBytes);

	/// Method for reading data from the receive_buffer.
	uint8_t* data_read();

	/// Method for establishing the UART connection.
	void connect();

	/// Method for dissolving the UART connection.
	void disconnect();

	/// Method for flushing the send_buffer and receive_buffer.
	/// Also flushes the RX and TX pins of the com port specified.
	void flush();

	/// Method for checking if the connection is established.
	bool is_open();

	/// Method for adding a listener to the listeners list.
	/// \param t TransportListener to be added
	void set_listener(TransportListener * t);

	/// Method for removing a listener to the listeners list.
	/// \param t TransportListener to be removed
	void remove_listener(TransportListener * t);

	/// Active method which should run in it's own thread. 
	/// Sends data in the send_buffer through the established connection, 
	/// and polls the com port for received data while putting it in the 
	/// receive_buffer.
	void run();

private:
	int comport;
	int baud;
	const char* mode;

	bool running = false;
	std::thread runningThread;
};

#endif
