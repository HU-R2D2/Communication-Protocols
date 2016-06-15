// TCPSocket.cpp : Defines the entry point for the console application.
#include "../include/TCPSocket.hpp"

TCPSocket::TCPSocket(std::string ipNr, std::string portNr) :
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
TCPSocket::~TCPSocket(){
	runningThread.join();
}
void TCPSocket::init() {
	std::cout << "initialise Winsock\n";
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
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
void TCPSocket::connect() {
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
	runningThread = std::thread(&TCPSocket::run, this);
	is_running = true;
	std::cout << ("Connected!\n");
}

void TCPSocket::data_write(uint8_t* data, int numberOfBytes) {
	std::cout << "\ndata_write done! \n" << std::endl;
	for (unsigned int i = 0; i < numberOfBytes; i++) {
		send_buffer.push(data[i]);
	}
}

uint8_t * TCPSocket::data_read() {
	uint8_t * data = new uint8_t[sizeof(receive_buffer)];
	if (!receive_buffer.empty()) {
		for (unsigned int i = 0; sizeof(receive_buffer); i++) {
			data[i] = receive_buffer.front();
			receive_buffer.pop();
		}
	}
	return data;
}

void TCPSocket::disconnect() {
	// shutdown the connection since no more data will be sent
	shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();
	is_running = false;
	std::cout << "Disconnected!\n";
}

void TCPSocket::flush() {
	std::queue<int> empty;
	std::queue<uint8_t>().swap(receive_buffer);
}

bool TCPSocket::is_open() {
	std::string data = "isOpen?";
	iResult = send(ConnectSocket, data.c_str(), (int)strlen(data.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		return false;
	}
	return true;
}

void TCPSocket::send_message() {
	int s = send_buffer.size();
	char data[DEFAULT_BUFLEN];
	if (!send_buffer.empty()) {
		for (int i = 0; i < s; i++) {
			data[i] = send_buffer.front();
			send_buffer.pop();
		}
		iResult = send(ConnectSocket, data, s, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << ("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			exit(EXIT_FAILURE);
		}
	}
}

void TCPSocket::send_message(uint8_t * d) {
	char *data = reinterpret_cast<char*>(d);
	iResult = send(ConnectSocket, data, (int)strlen(data), 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << ("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void TCPSocket::receive_message() {
	char* tempReceiveBuf = (char*)malloc(DEFAULT_BUFLEN);
	iResult = recv(ConnectSocket, tempReceiveBuf, DEFAULT_BUFLEN, 0);
	if (iResult > 0) {
		for (unsigned int i = 0; i < iResult; i++) {
			receive_buffer.push(tempReceiveBuf[i]);
		}
		for(auto &TransportListener : transportListeners){
			TransportListener->data_received( (uint8_t *)&tempReceiveBuf, iResult);
		}
	}
	else if (iResult == 0)
		std::cout << "Error: connection is closed";
	else if (iResult == 10093)
		std::cout << "receive timeout" << std::endl;
	else
		std::cout << "recv failed with error: " << WSAGetLastError() << "\n";
}

void TCPSocket::set_receive_timeout(unsigned int i) {
	int ret = setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&i,
		sizeof(int));
	if (ret == SOCKET_ERROR) {
		std::cout << "setsockopt() failed with error code " << WSAGetLastError()
		<< std::endl;
		exit(EXIT_FAILURE);
	}
}

void TCPSocket::set_listener(TransportListener * t){
	transportListeners.push_back(t);
}

void TCPSocket::remove_listener(TransportListener * t){
	transportListeners.erase(std::remove(transportListeners.begin(), transportListeners.end(), t), transportListeners.end());
}

void TCPSocket::run(){
	while (is_running) {
		Sleep(1500);
		if (is_open()) {
			std::cout <<"jaja"<<std::endl;
			send_message();
			receive_message();
		}
	}
}
