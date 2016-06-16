// TCPSocket.cpp : Defines the entry point for the console application.
#include "../include/TCPSocket.hpp"

TCPSocket::TCPSocket(std::string ip_nr, std::string port_nr) :
	ip_nr(ip_nr),
	port_nr(port_nr)
{
	init();
	i_result = getaddrinfo(ip_nr.c_str(), port_nr.c_str(), &hints, &result);
	if (i_result != 0) {
		std::cout << "\ngetaddrinfo failed with error:" << i_result;
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}
TCPSocket::~TCPSocket(){
	running_thread.join();
}
void TCPSocket::init() {
	std::cout << "initialise Winsock\n";
	i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (i_result != 0) {
		std::cout << "WSAStartup failed with error: " << i_result;
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
		i_result = ::connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (i_result == SOCKET_ERROR) {
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
	running_thread = std::thread(&TCPSocket::run, this);
	is_running = true;
	std::cout << ("Connected!\n");
}

void TCPSocket::data_write(uint8_t* data, int number_of_bytes) {
	std::cout << "\ndata_write done! \n" << std::endl;
	for (unsigned int i = 0; i < number_of_bytes; i++) {
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
	i_result = send(ConnectSocket, data.c_str(), (int)strlen(data.c_str()), 0);
	if (i_result == SOCKET_ERROR) {
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
		i_result = send(ConnectSocket, data, s, 0);
		if (i_result == SOCKET_ERROR) {
			std::cout << ("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			exit(EXIT_FAILURE);
		}
	}
}

void TCPSocket::send_message(uint8_t * d) {
	char *data = reinterpret_cast<char*>(d);
	i_result = send(ConnectSocket, data, (int)strlen(data), 0);
	if (i_result == SOCKET_ERROR) {
		std::cout << ("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void TCPSocket::receive_message() {
	char* tempReceiveBuf = (char*)malloc(DEFAULT_BUFLEN);
	i_result = recv(ConnectSocket, tempReceiveBuf, DEFAULT_BUFLEN, 0);
	if (i_result > 0) {
		for (unsigned int i = 0; i < i_result; i++) {
			receive_buffer.push(tempReceiveBuf[i]);
		}
		for(auto &TransportListener : transport_listeners){
			TransportListener->data_received( (uint8_t *)&tempReceiveBuf, i_result);
		}
	}
	else if (i_result == 0)
		std::cout << "Error: connection is closed";
	else if (i_result == 10093)
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
	transport_listeners.push_back(t);
}

void TCPSocket::remove_listener(TransportListener * t){
	transport_listeners.erase(std::remove(transport_listeners.begin(), transport_listeners.end(), t), transport_listeners.end());
}

void TCPSocket::run(){
	while (is_running) {
		Sleep(1500);
		if (is_open()) {
			send_message();
			receive_message();
		}
	}
}
