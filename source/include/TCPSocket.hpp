#ifndef HPP_TCPSOCKET
#define HPP_TCPSOCKET

//#include "ConnectionException.hpp"
#include "TransportProtocol.hpp"
#define _WIN32_WINNT 0x0501

#include <ws2tcpip.h>
#include <winsock2.h>	//winsock2.h contains most of the Winsock functions, structures, and definitions. 
#include <windows.h>
#include <string>
#include <queue>


#define WIN32_LEAN_AND_MEAN //used to exclude rarely-used services from Windows headers(to speed up building time)
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

class TCPSocket : public TransportProtocol {

public:
	TCPSocket(){}
	TCPSocket(std::string ipNr, std::string portNr);
	void t_init();

	void t_data_write(uint8_t* data);
	void t_data_write(std::string data);

	uint8_t* t_data_read();

	void t_connect();

	void t_disconnect();

	void t_flush();

	bool t_is_open();

private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	const std::string ipNr, portNr;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;
	bool isOpen = false;

	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;

};
#endif