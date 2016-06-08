#ifndef HPP_TCPSOCKET
#define HPP_TCPSOCKET

//#include "ConnectionException.hpp"
#include "TransportProtocol.hpp"
//#define _WIN32_WINNT 0x0501

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
	TCPSocket() {};
	TCPSocket(std::string ipNr, std::string portNr);
	void init();

	void data_write(uint8_t* data, int numberOfBytes);

	uint8_t* data_read();

	void connect();

	void disconnect();

	void flush();

	bool is_open();

	void receiveMessage();

	void sendMessage(std::string data);

	bool set_listener(TransportProtocol * t);

	//bool selistener(TCPSocket * t);

	bool remove_listener(TransportProtocol * t);

private:
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	const std::string ipNr, portNr;

	char tcp_recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int tcp_recvbuflen = DEFAULT_BUFLEN;
	bool isOpen = false;

	std::vector<TransportProtocol*> list;

	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;

};
#endif