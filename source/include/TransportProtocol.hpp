#ifndef _TRANSPORTPROTOCOL_HPP
#define _TRANSPORTPROTOCOL_HPP

#include <cstdint>

class TransportProtocol{

public:

	virtual void data_write(uint8_t* data) = 0;

	virtual uint8_t* data_read() = 0;

	virtual void connect() = 0;

	virtual void disconnect() = 0;

	virtual void flush() = 0;

	virtual bool is_open() = 0;
};

#endif