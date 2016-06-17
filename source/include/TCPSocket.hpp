//! \addtogroup 0023 - ComminucationProtocols
//! \brief Defines different commincation protocols for embedded systems.
//!
//! ComminucationProtocol is a project to determine the different ways embedded systems can comminucate with each other.
//!
//! \file   TCPSocket.hpp
//! \author Waila Woe
//! \date   Created: 16-6-2016
//! \date   Last Modified: 16-6-2016
//! \brief  TCPSocket is used as transportprotocol to comminucate over TCP
//!
//! Create a connection to a TCP server to send and receive data.
//!
//! \copyright Copyright © 2016, HU University of Applied Sciences Utrecht.
//! All rights reserved.
//!
//! License: newBSD
//!
//! Redistribution and use in source and binary forms,
//! with or without modification, are permitted provided that
//! the following conditions are met:
//! - Redistributions of source code must retain the above copyright notice,
//!   this list of conditions and the following disclaimer.
//! - Redistributions in binary form must reproduce the above copyright notice,
//!   this list of conditions and the following disclaimer in the documentation
//!   and/or other materials provided with the distribution.
//! - Neither the name of the HU University of Applied Sciences Utrecht
//!   nor the names of its contributors may be used to endorse or promote
//!   products derived from this software without specific prior written
//!   permission.
//!
//! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//! "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
//! BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
//! AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//! IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
//! BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//! CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//! PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//! OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//! WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//! OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//! EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ~< HEADER_VERSION 2016 04 12 >~

#ifndef HPP_TCPSOCKET
#define HPP_TCPSOCKET


#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>


#include <string>
#include <queue>
#include <thread>
#include <iostream>
#include <algorithm>
//#include "ConnectionException.hpp"
#include "TransportProtocol.hpp"
//#define _WIN32_WINNT 0x0501


#define WIN32_LEAN_AND_MEAN //used to exclude rarely-used services from Windows headers(to speed up building time)
#define DEFAULT_BUFLEN 4096

/// A protocol class for TCPSocket, wrapper for the winsock library.
/// \author Waila Woe
/// \version 1.0
/// \date 13-6-2016
class TCPSocket : public TransportProtocol, public std::thread {

public:
	///The constructor for TCP
	///\param ipNr The ip addres you want to connect to
	///\param portNR The port number which it will be connected to
	TCPSocket(std::string ip_nr, std::string port_nr);

	~TCPSocket();

	///Initialize winsock
	///Will be called in the constructor to initialize winsock.
	///Do not change this.
	void init();

	///Writes data to the send_buffer queue.
	///\param data The data to be send.
	///\param numberOfBytes Number of bytes that data contains.
	void data_write(uint8_t* data, int number_of_bytes) override;

	///Reads data from the receive_buffer queue.
	uint8_t* data_read() override;

	///Establisching the TCP connection.
	void connect() override;
	///Disconnet the TCP connection.
	void disconnect() override;

	///Flushes the send_buffer & receive_buffer .
	void flush() override;


	//Checks wether the connection is open.
	bool is_open() override;

	///Checks for messages in the send_buffer queue to send to the
	///connected TCP Connection.
	void send_message();

	///Sends the given message to the connected TCP connection
	void send_message(uint8_t * d);

	///Waits untill data is received from the sender and puts the
	///received data in the receive_buffer queue.
	void receive_message();

	///Sets the timeout for
	void set_receive_timeout(unsigned int i);

	/// Method for adding a listener to the listeners list.
	/// \param t TransportListener to be added
	void set_listener(TransportListener * t) override;

	/// Method for removing a listener to the listeners list.
	/// \param t TransportListener to be removed
	void remove_listener(TransportListener * t) override;

	/// Active method which should run in it's own thread.
	/// Sends data in the send_buffer through the established connection,
	/// and polls for received data while putting it in the receive_buffer.
	void run();


private:
	WSADATA wsa_data;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	const std::string ip_nr, port_nr;
	std::thread running_thread;
	int i_result;
	bool is_opened = false;
	bool is_running = false;
};

#endif
