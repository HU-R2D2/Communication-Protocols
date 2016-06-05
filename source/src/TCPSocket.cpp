// TCPSocket.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "../include/TCPSocket.hpp"

TCPSocket::TCPSocket(std::string ipNr, std::string portNr):
	ipNr(ipNr),
	portNr(portNr)
{
	t_init();	
	// Resolve the server address and port
	const char* ipNumber = ipNr.c_str();		//TIJDELIJK DIT KAN ANDERS?
	const char* portNumber = portNr.c_str();	//dunno why
	iResult = getaddrinfo(ipNumber, portNumber, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		exit(EXIT_FAILURE);
	}

}

void TCPSocket::t_init() {
	printf("initialise Winsock");
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //MAKEWORD(2.2) makes request for winsock version 2.2, WSAStartup iniate use of the WS2_32.dll
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		exit(EXIT_FAILURE);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	printf("Initialised");
}

void TCPSocket::t_connect() {
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(EXIT_FAILURE);
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	printf("Connected!");
}


void TCPSocket::t_data_write(uint8_t* data) {
	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	printf("Bytes Sent: %ld\n", iResult);
}

uint8_t * TCPSocket::t_data_read(){
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());

	} 
	while (iResult > 0);
	closesocket(ConnectSocket);
	WSACleanup(); //Terminates use of the Ws2_32.DLL.
	
	return (uint8_t*) recvbuf;
	//HIER WAS IK GEBLEVEN EN DE RETURN IS NET GEDAAN
}


void TCPSocket::t_disconnect(){
	// shutdown the connection since no more data will be sent
	shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();
}

void TCPSocket::t_flush(){
}

bool TCPSocket::t_is_open(){
	return isOpen;
}

