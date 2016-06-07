// TCPSocket.cpp : Defines the entry point for the console application.
#include "../include/TCPSocket.hpp"
#include <iostream>
#include <sstream>



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
		std::cout << "getaddrinfo failed with error:" << iResult;
		WSACleanup();
		exit(EXIT_FAILURE);
	}

}

void TCPSocket::t_init() {
	std::cout << "initialise Winsock\n";
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //MAKEWORD(2.2) makes request for winsock version 2.2, WSAStartup iniate use of the WS2_32.dll
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: " << iResult;
		exit(EXIT_FAILURE);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	std::cout << "Initialised\n";
}

void TCPSocket::t_connect() {
	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			std::cout << "socket failed with error: " << WSAGetLastError();
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
		std::cout << ("Unable to connect to server!\n");
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	std::cout << ("Connected!");

	/*
	if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %ld\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            printf("Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );
	*/
}


void TCPSocket::t_data_write(uint8_t* data) {
	//vin send buffr zetten en versturen
	//check if empty
	for (int i = 0; i < sizeof(data); i++) {
		receive_buffer.push(data[i]);
	}
}

void TCPSocket::t_data_write(std::string data) {
	//uint8_t * data = new uint8_t[sizeof(send_buffer)];
}

uint8_t * TCPSocket::t_data_read(){
	//uint8 char lezen naar een pointer en die returnen
	uint8_t * data = new uint8_t[sizeof(send_buffer)];
	if ( !send_buffer.empty() ) {
		for (int i = 0; i < sizeof(send_buffer); i++) {
			data[i] = send_buffer.front();
			send_buffer.pop();
		}
	}
	else {
		//exit(EXIT_FAILURE);
	}
	return data;
}


void TCPSocket::t_disconnect(){
	// shutdown the connection since no more data will be sent
	shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();
}

void TCPSocket::t_flush(){
	std::queue<int> empty;
	std::queue<uint8_t>().swap(receive_buffer);
}

bool TCPSocket::t_is_open(){
	return isOpen;
}

int main() {
	TCPSocket * sock1 = new TCPSocket("127.0.0.1", "27015");
	std::cout << sock1->t_data_read();
	uint8_t * data = new uint8_t[5];
	

	std::string s = "haha";
	const char * c = s.c_str();
	for (int i = 0; i < sizeof(c); i++) {
		data[i] = c[i];
	}
	std::cout << ("data write\n");
	sock1->t_data_write(data);
	data = sock1->t_data_read();
	std::stringstream ss;
	ss << data;
	std::cout << "BALBAL\n";
	std::cout << ss.str();
	std::cout << ("connect)\n");

	int x = 0xa1a56;
	std::stringstream ss;
	ss << x;
	std::cout << "\nOHEHOE" << ss.str();

	sock1->t_connect();
}

