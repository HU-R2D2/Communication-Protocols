#ifndef _TRANSPORTPROTOCOL_HPP
#define _TRANSPORTPROTOCOL_HPP

#include <cstdint>
#include <queue>
#include <vector>
#include "TransportListener.hpp"

class TransportProtocol{

public:
	//TransportProtocol();
	//~TransportProtocol();

	virtual void data_write(uint8_t* data, int number_of_bytes) = 0;

	virtual uint8_t* data_read() = 0;

	virtual void connect() = 0;

	virtual void disconnect() = 0;

	virtual void flush() = 0;

	virtual bool is_open() = 0;

	virtual void set_listener(TransportListener * t) = 0;

	virtual void remove_listener(TransportListener * t) = 0;

protected:

	std::vector<TransportListener *> transport_listeners;

	std::queue<uint8_t> send_buffer;

	std::queue<uint8_t> receive_buffer;
};

#endif
