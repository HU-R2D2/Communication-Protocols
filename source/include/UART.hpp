//! \addtogroup 0023 - ComminucationProtocols
//! \brief Defines different commincation protocols for embedded systems.
//!
//! ComminucationProtocol is a project to determine the different ways embedded systems can comminucate with each other.
//!
//! \file   UART.hpp
//! \author Thijs Hendrickx
//! \date   Created: 16-6-2016
//! \date   Last Modified: 16-6-2016
//! \brief  UART is a protocol to transfer data via a serial interface.
//!
//! UART is  a TransportProtocol and can be used to send and receive data over the serial interface.
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


#ifndef _UART_HPP
#define _UART_HPP

#include <queue>
#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>
#include "TransportProtocol.hpp"
#include "ComportDefines.hpp"
#include "../../../deps/rs232/rs232.h"

typedef unsigned int uint;

/// A protocol class for UART, wrapper for the RS232 library.
/// \author Thijs Hendrickx
/// \version 1.0
/// \date 13-6-2016
class UART : public TransportProtocol, public std::thread{

public:

	/// Constructor for initialising UART connection.
	/// \param comport_nr The com port which to connect to.
	/// This is for example COM4 for windows or ttyUSb4 for linux.
	/// Full list of defines can be found in comport_defines.hpp
	/// \param baudrate The baudrate to use when sending and
	/// receiving data over the selected com port.
	/// \param mode The settings to use for the connection,
	/// data bits, parity and stopbits.
	UART(int comport_nr, int baudrate = 9600, const char* mode = "8N1");

	/// Destructor for UART connection.
	~UART();

	/// Method for writing data to the send_buffer queue,
	/// for it to be send through the com port.
	/// \param data The data to be send
	/// \param numberOfBytes Length of the data in bytes
	void data_write(uint8_t* data, int numberOfBytes) override;

	/// Method for reading data from the receive_buffer.
	uint8_t* data_read() override;

	/// Method for establishing the UART connection.
	void connect() override;

	/// Method for dissolving the UART connection.
	void disconnect() override;

	/// Method for flushing the send_buffer and receive_buffer.
	/// Also flushes the RX and TX pins of the com port specified.
	void flush() override;

	/// Method for checking if the connection is established.
	bool is_open() override;

	/// Method for adding a listener to the listeners list.
	/// \param t TransportListener to be added
	void set_listener(TransportListener * t) override;

	/// Method for removing a listener to the listeners list.
	/// \param t TransportListener to be removed
	void remove_listener(TransportListener * t) override;

	/// Active method which should run in it's own thread.
	/// Sends data in the send_buffer through the established connection,
	/// and polls the com port for received data while putting it in the
	/// receive_buffer.
	void run();

private:
	int comport;
	int baud;
	const char* mode;

	bool running = false;
	std::thread runningThread;
};

#endif
