#ifndef HPP_TCPSOCKET
#define HPP_TCPSOCKET

#include "ConnectionException.hpp"
#include "TransportProtocol.hpp"
#include <winsock2.h>	//winsock2.h contains most of the Winsock functions, structures, and definitions. 
#include <ws2tcpip.h>	//contains definitions introduced in the WinSock 2 Protocol-Specific Annex document for TCP/IP that includes newer functions and structures used to retrieve IP addresses. 
#include <queue>

#pragma comment(lib, "Ws2_32.lib") //tells to the linker that Ww2_32.lib is needed


class TCPSocket : public TransportProtocol {	struct addrinfo 
		*result = NULL,
		*ptr = NULL,
		hints;
public:
	TCPSocket();
	TCPSocket(std::string ipNr, std::string portNr);
	
	~TCPSocket();

	void initializeSocket();

	void data_write(uint8_t* data);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

private:
	struct addrinfo
		*result = NULL,
		*ptr = NULL,
		hints;
	SOCKET ConnectSocket = INVALID_SOCKET;
	
	std::string portNumber, ipNumber;
	int iResult;
	//contains info about Windows Socket implementation, which enables us to use winsock functions
	WSAData wsaData; 


	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;
	char *recv_buf;
	int bufLen;
};
#endif