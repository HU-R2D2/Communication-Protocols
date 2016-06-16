#include "../include/TCP_Windows.hpp"

TCP_Windows::TCP_Windows(std::string ipNr, std::string portNr) :
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
TCP_Windows::~TCP_Windows(){
	runningThread.join();
}
void TCP_Windows::init() {
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: " << iResult;
		exit(EXIT_FAILURE);
	}
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	std::cout << "Initialised Winsock\n";
}
void TCP_Windows::connect() {
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			std::cout << "\nsocket failed with error: " << WSAGetLastError();
			WSACleanup();
			exit(EXIT_FAILURE);
		}
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
	runningThread = std::thread(&TCP_Windows::run, this);
	is_running = true;
	std::cout << ("Connected!\n");
}

void TCP_Windows::data_write(uint8_t* data, int numberOfBytes) {
	std::cout << "\ndata_write done! \n" << std::endl;
	for (int i = 0; i < numberOfBytes; i++) {
		send_buffer.push(data[i]);
	}
}

uint8_t * TCP_Windows::data_read() {
	uint8_t * data = new uint8_t[sizeof(receive_buffer)];
	if (!receive_buffer.empty()) {
		for (unsigned int i = 0; sizeof(receive_buffer); i++) {
			data[i] = receive_buffer.front();
			receive_buffer.pop();
		}
	}
	return data;
}

void TCP_Windows::disconnect() {
	shutdown(ConnectSocket, SD_SEND);
	closesocket(ConnectSocket);
	WSACleanup();
	is_running = false;
	std::cout << "Disconnected!\n";
}

void TCP_Windows::flush() {
	std::queue<int> empty;
	std::queue<uint8_t>().swap(receive_buffer);
}

bool TCP_Windows::is_open() {
	std::string data = "isOpen?";
	iResult = send(ConnectSocket, data.c_str(), (int)strlen(data.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		return false;
	}
	return true;
}

void TCP_Windows::send_message() {
	int s = send_buffer.size();
	char data[DEFAULT_BUFLEN];
	if (!send_buffer.empty()) {
		for (int i = 0; i < s; i++) {
			data[i] = send_buffer.front();
			send_buffer.pop();
		}
		iResult = send(ConnectSocket, data, s, 0);
		if (iResult == SOCKET_ERROR) {
			std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ConnectSocket);
			WSACleanup();
			exit(EXIT_FAILURE);
		}
	}
}

void TCP_Windows::send_message(uint8_t * d) {
	char *data = reinterpret_cast<char*>(d);
	iResult = send(ConnectSocket, data, (int)strlen(data), 0);
	if (iResult == SOCKET_ERROR) {
		std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		exit(EXIT_FAILURE);	
	}
}

void TCP_Windows::receive_message() {
	char* tempReceiveBuf = (char*)malloc(DEFAULT_BUFLEN);
	iResult = recv(ConnectSocket, tempReceiveBuf, DEFAULT_BUFLEN, 0);
	if (iResult > 0) {
		for (int i = 0; i < iResult; i++) {
			receive_buffer.push(tempReceiveBuf[i]);
		}
		for(auto &TransportListener : transportListeners){
			TransportListener->data_received( (uint8_t *)&tempReceiveBuf);
		}
	}
	else if (iResult == 0)
		std::cout << "Error: didn't receive anything";
	else if (iResult == 10093)
		std::cout << "receive timeout" << std::endl;
}

void TCP_Windows::set_receive_timeout(unsigned int i) {
	int ret = setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&i, 
		sizeof(int));
	if (ret == SOCKET_ERROR) {
		std::cout << "setsockopt() failed with error code " << WSAGetLastError() 
		<< std::endl;
		exit(EXIT_FAILURE);
	}
}

void TCP_Windows::set_listener(TransportListener * t){
	transportListeners.push_back(t);
}

void TCP_Windows::remove_listener(TransportListener * t){
	transportListeners.erase(std::remove(transportListeners.begin(), transportListeners.end(), t), transportListeners.end());
}

void TCP_Windows::run(){
	while (is_running) {
		if (is_open()) {
			std::cout <<"jaja"<<std::endl;
			send_message();
			receive_message();
		}
		Sleep(100);
	}	
}

int main() {
	TCP_Windows sock1("127.0.0.1", "27015");
	
	sock1.connect();
	sock1.set_receive_timeout(1000);
	Sleep(1000);
	std::cout<<"send wailawoe to server"<<std::endl;
	sock1.data_write((uint8_t *) "wailawoe", 8);
	Sleep(1000);
	sock1.data_write((uint8_t *) "halloiets", 9);
	Sleep(1000);

	sock1.disconnect();
}