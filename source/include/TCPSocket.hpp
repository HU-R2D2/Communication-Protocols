#ifndef HPP_TCPSOCKET
#define HPP_TCPSOCKET

//#include "ConnectionException.hpp"
#include "TransportProtocol.hpp"
#include <winsock2.h>	//winsock2.h contains most of the Winsock functions, structures, and definitions. 
#include <ws2tcpip.h>	//contains definitions introduced in the WinSock 2 Protocol-Specific Annex document for TCP/IP that includes newer functions and structures used to retrieve IP addresses. 
#include <windows.h>
#include <queue>

#define WIN32_LEAN_AND_MEAN //used to exclude rarely-used services from Windows headers(to speed up building time)
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#pragma comment(lib, "Ws2_32.lib") //tells to the linker that Ww2_32.lib is needed
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class TCPSocket : public TransportProtocol {

public:
	TCPSocket(std::string ipNr, std::string portNr);

	void t_data_write(uint8_t* data);

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

	std::string portNr, ipNr;
	char *sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;

};
#endif