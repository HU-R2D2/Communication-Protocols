//! \addtogroup 0023 - ComminucationProtocols
//! \brief Defines different commincation protocols for embedded systems.
//!
//! ComminucationProtocol is a project to determine the different ways embedded systems can comminucate with each other.
//!
//! \file   RestApplicationProtocol.hpp
//! \author Koen van der Kruk, 1654581
//! \date   Created: 16-6-2016
//! \date   Last Modified: 16-6-2016
//! \brief  ApplicationProtocol to comminucate with REST over a transport protocol.
//!
//! Used to setup a RestApplicationProtocol with support for REST over TCP or UART transport protocol.
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

#ifndef _REST_PROTOCOL_HPP
#define _REST_PROTOCOL_HPP

#include "ApplicationProtocol.hpp"
#include "TransportListener.hpp"
#include <fstream>
#include <iostream>
#include "../../../deps/REST/include/RESTCallBack.hpp"
#include "../../../deps/REST/include/RESTEngine.hpp"
#include <string>
#include <vector>


/// An extension on ApplicationProtocol with support for REST api.
/// \author Koen van der Kruk
/// \version 1.0
/// \date 8-6-2016
class RestApplicationProtocol : public TransportListener, public ApplicationProtocol{

public:

    /// Second constructor with support for the TransportProtocol.
    RestApplicationProtocol(TransportProtocol & t);

    /// Destructs the ApplicationProtocol object so the TransportProtocol is also removed.
    ~RestApplicationProtocol();

    /// This will assign a new function as callback function.
    /// \param link The http url to access
    /// \param method The http method, such as POST, PUT, DELETE, GET
    /// \param callBackAddition The function that receives the callback message.
    void addCallbackFunction(std::string link, std::string method, RESTCallBack * callback_addition);

    //// RestApplicationProtocol is a TransportListener that will receive incoming messages.
    /// \param data The incoming data package
    void data_received(uint8_t * data, int number_of_bytes) override;

    /// Invoke API call, callback to another function.
    /// \param link The url conencted to the callback function
    /// \param method The HTTP method that can be used to invoke an API call over HTTP.
    /// \param message The message for the callback function
    void invokeApiCall(std::string link, std::string method, std::string message);

    /// This function will dump a full REST api in json format.
    /// \param fileName The filename is used to dump the REST API in json format. The same directory is used as the current running program.
    void getJsonAPIDump(std::string file_name);

private:
    RESTEngine engine;
};

#endif
