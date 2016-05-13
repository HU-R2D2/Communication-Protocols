// TCPSocket.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include "include/TCPSocket.hpp"

TCPSocket::TCPSocket(){

}

TCPSocket::TCPSocket(std::string ipNr, std::string portNr) :
	ipNumber(ipNr),
	portNumber(portNr)
{
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData); //MAKEWORD(2.2) makes request for winsock version 2.2, WSAStartup iniate use of the WS2_32.dll
	if (iResult != 0) {
		//ERROR HANDLING
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

TCPSocket::~TCPSocket(){
}

void TCPSocket::initializeSocket(){
}

void TCPSocket::data_write(uint8_t* data) {
}

uint8_t * TCPSocket::data_read(){
	do {
		iResult = recv(ConnectSocket, recv_buf, bufLen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());

	} 
	while (iResult > 0);
	closesocket(ConnectSocket);
	WSACleanup();
	//HIER WAS IK GEBLEVEN EN DE RETURN IS NET GEDAAN
	
	return (uint8_t*) recv_buf;
}

void TCPSocket::connect(){
}

void TCPSocket::disconnect(){
	closesocket(ConnectSocket);
	WSACleanup();
}

void TCPSocket::flush(){
}

bool TCPSocket::is_open(){
	return false;
}


