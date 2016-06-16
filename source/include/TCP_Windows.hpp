#ifndef HPP_TCP_WINDOWS
#define HPP_TCP_WINDOWS

#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>

#include <string>
#include <queue>
#include <thread>
#include <iostream>
#include <algorithm>
//#include "ConnectionException.hpp"
#include "TransportProtocol.hpp"



#define WIN32_LEAN_AND_MEAN 
#define DEFAULT_BUFLEN 4096

/// A protocol class for TCP_Windows, wrapper for the winsock library.
/// \author Waila Woe
/// \version 1.0
/// \date 13-6-2016
class TCP_Windows : public TransportProtocol, public std::thread {

public:
	///The constructor for TCP 
	///\param ipNr The ip addres you want to connect to
	///\param portNR The port number which it will be connected to
	TCP_Windows(std::string ipNr, std::string portNr);

	~TCP_Windows();

	///Initialize winsock
	///Will be called in the constructor to initialize winsock. 
	///Do not change this.
	void init();

	///Writes data to the send_buffer queue. 
	///\param data The data to be send.
	///\param numberOfBytes Number of bytes that data contains.
	void data_write(uint8_t* data, int numberOfBytes);

	///Reads data from the receive_buffer queue.
	uint8_t* data_read();

	///Establisching the TCP connection.
	void connect();
	///Disconnet the TCP connection.
	void disconnect();

	///Flushes the send_buffer & receive_buffer .
	void flush();

	//Checks wether the connection is open.
	bool is_open();

	///Checks for messages in the send_buffer queue to send to the 
	///connected TCP Connection.
	void send_message();

	///Sends the given message to the connected TCP connection
	void send_message(uint8_t * d);

	///Waits untill data is received from the sender and puts the
	///received data in the receive_buffer queue.
	void receive_message();

	///Sets the timeout for 
	void set_receive_timeout(unsigned int i);

	/// Method for adding a listener to the listeners list.
	/// \param t TransportListener to be added
	void set_listener(TransportListener * t);

	/// Method for removing a listener to the listeners list.
	/// \param t TransportListener to be removed
	void remove_listener(TransportListener * t);

	/// Active method which should run in it's own thread. 
	/// Sends data in the send_buffer through the established connection, 
	/// and polls for received data while putting it in the receive_buffer.
	void run();


private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	const std::string ipNr, portNr;
	std::thread runningThread;
	int iResult;
	bool isOpen = false;
	bool is_running = false;
};

#endif