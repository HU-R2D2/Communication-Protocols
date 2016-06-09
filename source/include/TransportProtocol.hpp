#ifndef _TRANSPORTPROTOCOL_HPP
#define _TRANSPORTPROTOCOL_HPP

#include <cstdint>
#include "TransportListener.hpp"

class TransportProtocol{

public:
	//TransportProtocol();
	//~TransportProtocol();

	virtual void t_data_write(uint8_t* data) = 0;

	virtual uint8_t* t_data_read() = 0;

	virtual void t_connect() = 0;

	virtual void t_disconnect() = 0;

	virtual void t_flush() = 0;

	virtual bool t_is_open() = 0;

	virtual bool t_set_listener(TransportListener * t) = 0;

	virtual bool t_remove_listener(TransportListener * t) = 0;


private:

};

#endif
