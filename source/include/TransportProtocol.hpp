//! \addtogroup 0023 - ComminucationProtocols
//! \brief Defines different commincation protocols for embedded systems.
//!
//! ComminucationProtocol is a project to determine the different ways embedded systems can comminucate with each other.
//!
//! \file   TransportProtocol.hpp
//! \author Koen van der Kruk, 1654581
//! \date   Created: 16-6-2016
//! \date   Last Modified: 16-6-2016
//! \brief  A default interface for TransportProtocol to make sure
//!
//! TransportProtocol is a default implementation to create a transportprotocol such as uart and tcp.
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

#ifndef _TRANSPORTPROTOCOL_HPP
#define _TRANSPORTPROTOCOL_HPP

#include <cstdint>
#include <queue>
#include <vector>
#include "TransportListener.hpp"

class TransportProtocol{

public:

	/// Method for writing data to the send_buffer queue,
	/// for it to be send through the com port.
	/// \param data The data to be send
	/// \param numberOfBytes Length of the data in bytes
	virtual void data_write(uint8_t* data, int number_of_bytes) = 0;

	/// Method for reading data from the receive_buffer.
	virtual uint8_t* data_read() = 0;

	/// Method for establishing the  connection.
	virtual void connect() = 0;

	/// Method for dissolving the connection.
	virtual void disconnect() = 0;

	/// Method for flushing the send_buffer and receive_buffer.
	virtual void flush() = 0;

	/// Method for checking if the connection is established.
	virtual bool is_open() = 0;

	/// Method for adding a listener to the listeners list.
	/// \param t TransportListener to be added
	virtual void set_listener(TransportListener * t) = 0;

	/// Method for removing a listener to the listeners list.
	/// \param t TransportListener to be removed
	virtual void remove_listener(TransportListener * t) = 0;

protected:

	std::vector<TransportListener *> transport_listeners;

	std::queue<uint8_t> send_buffer;

	std::queue<uint8_t> receive_buffer;
};

#endif
