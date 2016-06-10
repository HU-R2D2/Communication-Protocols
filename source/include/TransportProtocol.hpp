#ifndef _TRANSPORTPROTOCOL_HPP
#define _TRANSPORTPROTOCOL_HPP

#include <cstdint>
#include "TransportListener.hpp"

class TransportProtocol{

public:
	//TransportProtocol();
	//~TransportProtocol();

	virtual void data_write(uint8_t* data, int numberOfBytes) = 0;

	virtual uint8_t* data_read() = 0;

	virtual void connect() = 0;

	virtual void disconnect() = 0;

	virtual void flush() = 0;

	virtual bool is_open() = 0;

	virtual bool t_set_listener(TransportListener * t) = 0;

	virtual bool t_remove_listener(TransportListener * t) = 0;

};

#endif
