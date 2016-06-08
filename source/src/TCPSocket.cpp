// TCPSocket.cpp : Defines the entry point for the console application.
#include "../include/TCPSocket.hpp"
#include <iostream>



TCPSocket::TCPSocket(std::string ipNr, std::string portNr):
	ipNr(ipNr),
	portNr(portNr)
{
	init();	
	iResult = getaddrinfo(ipNr.c_str(), portNr.c_str(), &hints, &result);
	if (iResult != 0) {
		std::cout << "\ngetaddrinfo failed with error:" << iResult;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void TCPSocket::init(){
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
void TCPSocket::connect(){

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			std::cout << "\nsocket failed with error: " << WSAGetLastError();
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		// Connect to server.
		iResult = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
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
	isOpen = true;
	std::cout << ("Connected!\n");
	sendMessage("go");
	receiveMessage();
}

void TCPSocket::data_write(uint8_t* data, int numberOfBytes) {
	//vin send buffr zetten en versturen
	for (unsigned int i = 0; i < sizeof(data); i++) {
		send_buffer.push(data[i]);
	}
}

uint8_t * TCPSocket::data_read(){
	uint8_t * data = new uint8_t[sizeof(receive_buffer)];
	if (!receive_buffer.empty()) {
		for (unsigned int i = 0; i < sizeof(receive_buffer); i++) {
			data[i] = receive_buffer.front();
			receive_buffer.pop();
		}
	}
	return data;
}

void TCPSocket::disconnect(){
	// shutdown the connection since no more data will be sent
	shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();
	isOpen = false;
	std::cout << "Disconnected!\n";
}

void TCPSocket::flush(){
	std::queue<int> empty;
	std::queue<uint8_t>().swap(receive_buffer);
}

bool TCPSocket::is_open(){
	return isOpen;
}

void TCPSocket::receiveMessage(){
	iResult = recv(ConnectSocket, tcp_recvbuf, tcp_recvbuflen, 0);
	if (iResult > 0) {
		std::cout << "SIZE OF iResult: " << iResult << "\n\n";
		for (unsigned int i = 0; i < iResult; i++) {
			receive_buffer.push(tcp_recvbuf[i]);
		}
		//std::cout << "Message received: " << recvbuf << " Bytes received: " << iResult << "\n";
	}
	else if (iResult == 0)
		std::cout << "Error: connection is closed";
	else
		std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
}

void TCPSocket::sendMessage(std::string data){
	// Send an initial buffer
	iResult = send(ConnectSocket, data.c_str(), (int)strlen(data.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << ("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	std::cout << iResult << " bytes message: \"" << data << "\" sent\n";
}

bool TCPSocket::set_listener(TransportProtocol * t){
	//list.push_back(t);
	return false;
}

bool TCPSocket::remove_listener(TransportProtocol * t){
	//list.erase(std::remove(list.begin(), list.end(), t), list.end());
	return false;
}

int main(){
	TCPSocket* sock1 = new TCPSocket("127.0.0.1", "27015");
	sock1->connect();
	sock1->sendMessage("halllo ik ben test!");
	sock1->disconnect();
	std::cout << sock1->data_read();
}
