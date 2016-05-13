#ifndef _TRANSPORTPROTOCOL_HPP
#define _TRANSPORTPROTOCOL_HPP

#include <cstdint>
#include <queue>

class TransportProtocol{

public:
	TransportProtocol();
	~TransportProtocol();

    //Writes the data to the receiver by putting it into the send_buffer.
    //This method throws ConnectionExceptions when something is wrong
	virtual void data_write(uint8_t* data, int numberOfBytes) = 0;

    //Reads the data om the receivebuffer. Can be empty.
    //This method throws ConnectionExceptions when something is wrong
	virtual uint8_t* data_read() = 0;

    //Connects to the receiver.
    //This method throws ConnectionExceptions when something is wrong
	virtual void connect() = 0;

    //Disconnects the receiver.
    //This method throws ConnectionExceptions when something is wrong
	virtual void disconnect() = 0;

    //Flushes the output buffer. Can block, depending on the implementation
    //This method throws ConnectionExceptions when something is wrong
	virtual void flush() = 0;

    //returns a bool indicating if the line is still open
    //This method throws ConnectionExceptions when something is wrong
	virtual bool is_open() = 0;

private:
	std::queue<uint8_t> send_buffer;
	std::queue<uint8_t> receive_buffer;
};

#endif